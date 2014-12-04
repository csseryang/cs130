// Name:
// Quarter, Year:
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <cmath>
#include <list>
#include <GL/glut.h>
#include "Point2D.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const float VIEW_LEFT = 0.0;
const float VIEW_RIGHT = WINDOW_WIDTH;
const float VIEW_BOTTOM = 0.0;
const float VIEW_TOP = WINDOW_HEIGHT;
const float VIEW_NEAR = -400;
const float VIEW_FAR = 400;


// Retrieve random float
float randFloat()
{
	return rand() / static_cast<float>(RAND_MAX);
}
float randFloat(float min, float max)
{
	return randFloat() * (max - min) + min;
}


// A simple wrapper for store 3D vectors
struct Vector3
{
	float x;
	float y;
	float z;


	Vector3() : x(0.0), y(0.0), z(0.0)
	{}


	Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{}


	Vector3(const Vector3 & v)
		: x(v.x), y(v.y), z(v.z)
	{}


	Vector3 operator+(const Vector3 & rhs) const
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	Vector3 operator-(const Vector3 & rhs) const
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	Vector3 operator*(float rhs) const
	{
		return Vector3(x * rhs, y * rhs, z * rhs);
	}
	Vector3 operator/(float rhs) const
	{
		return Vector3(x / rhs, y / rhs, z / rhs);
	}
	Vector3 operator+=(const Vector3 & rhs)
	{
		x += rhs.x; y += rhs.y; z += rhs.z; return *this;
	}
	Vector3 operator-=(const Vector3 & rhs)
	{
		x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this;
	}
	Vector3 operator*=(float rhs)
	{
		x *= rhs; y *= rhs; z *= rhs; return *this;
	}
	Vector3 operator/=(float rhs)
	{
		x /= rhs; y /= rhs; z /= rhs; return *this;
	}


	float magnitude() const
	{
		return sqrt(x * x + y * y + z * z);
	}
	void normalize()
	{
		*this /= magnitude();
	}
	Vector3 normalized() const
	{
		return *this / magnitude();
	}
	float dot(const Vector3 & rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	Vector3 cross(const Vector3 & rhs) const
	{
		return Vector3(y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x);
	}
};


// A simple wrapper to store colors
struct Color3d
{
	float r;
	float g;
	float b;
	float a;


	Color3d()
		: r(0.0), g(0.0), b(0.0), a(1.0)
	{}
	Color3d(float r, float g, float b, float a = 1.0)
		: r(r), g(g), b(b), a(a)
	{}
};
struct Particle
{
	// Important attributes of a particle which are respectively
	// position, velocity, acceleration, color, and lifetime timer.
	Vector3 pos;
	Vector3 vel;
	Vector3 acc;
	Color3d col;
	float timer;

	Particle()
		: pos(), vel(), col(), acc(), timer(0.0)
	{}
	Particle(const Vector3 & pos, const Vector3 & vel, const Vector3 & acc, const Color3d & col, float timer)
		: pos(pos), vel(vel), acc(acc), col(col), timer(timer)
	{}


	/* Complete this function */
	bool isExpired() const
	{
		if (timer * 10 < 30) //过期时间，自己改
			return false;
		return true;
	}


	/* Complete this function */
	void update(float elapsed)  //更新函数，不必改
	{
		pos = pos + vel * elapsed;
		vel = vel + acc * elapsed;
		timer += elapsed;
	}


	void render()
	{
		glColor4f(col.r, col.g, col.b, col.a);
		glVertex3f(pos.x, pos.y, pos.z);
	}
};
Point2D GLscreenToWindowCoordinate(const Point2D& p){
	GLdouble model[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	Point2D converted;
	GLdouble temp;
	gluUnProject(p.x, viewport[3] - p.y, 0, model,
		projection, viewport, &converted.x, &converted.y, &temp);
	return converted;
}


struct ParticleSystem
{
	// List of all unexpired particles
	std::list<Particle> particles;

	ParticleSystem(const Vector3 & spawnPoint)
		: particles()
	{
		init(spawnPoint);
	}


	/* Complete this function */
	void init(const Vector3 & spawnPoint)
	{
		int i;

		float vmin = 1.0, vmax = 5.0;  //速度范围，后面要用，
		float cmin = 0.0, cmax = 1.0;  //颜色范围，后面要用，
		float amin = -5.0, amax = 5.0; //加速度范围，后面要用，

		for (i = 0; i < 2000; i++)  //圆内点的数目，要改
		{
			double R = 50;  //球的半径，要改
			float myX = randFloat(spawnPoint.x - R, spawnPoint.x + R); //球的X范围，改下变量名
			float myY = randFloat(  //球的y范围，改下变量名
				spawnPoint.y - sqrt(R * R - (myX - spawnPoint.x)*(myX - spawnPoint.x)),
				spawnPoint.y + sqrt(R * R - (myX - spawnPoint.x)*(myX - spawnPoint.x))
				);

			float myZ = randFloat(  //球的z范围，改下变量名
				spawnPoint.z - sqrt(R * R - (myX - spawnPoint.x)*(myX - spawnPoint.x) - (myY - spawnPoint.y)*(myY - spawnPoint.y)),
				spawnPoint.z + sqrt(R * R - (myX - spawnPoint.x)*(myX - spawnPoint.x) - (myY - spawnPoint.y)*(myY - spawnPoint.y))
				);

			Particle temp;                     //每次操作一个点
			temp.pos.x = myX;                  //点位置
			temp.pos.y = myY;
			temp.pos.z = myZ;

			temp.vel.x = randFloat(vmin, vmax); //点的速度
			temp.vel.y = randFloat(vmin, vmax);
			temp.vel.z = randFloat(vmin, vmax);

			temp.acc.x = randFloat(amin, amax); //点的加速度
			temp.acc.y = randFloat(amin, amax);
			temp.acc.y = randFloat(amin, amax);

			temp.col.r = randFloat(cmin, cmax);//点的颜色
			temp.col.g = randFloat(cmin, cmax);
			temp.col.b = randFloat(cmin, cmax);
			temp.col.a = 1.0;
			particles.push_back(temp); //把点加入粒子系统
		}
	}


	/* Returns true if there are no particles present */
	bool isEmpty() const
	{
		return particles.size() <= 0;
	}


	void update(float elapsed)
	{
		std::list<Particle>::iterator it;


		// Update all particles
		for (it = particles.begin(); it != particles.end(); ++it)
		{
			it->update(elapsed);
		}

		// Remove any expired particles from the list
		for (it = particles.begin(); it != particles.end();)
		{
			if (it->isExpired())
				it = particles.erase(it);
			else
				++it;
		}
	}


	/* Renders all particles as single points */
	void render()
	{
		glBegin(GL_POINTS);
		std::list<Particle>::iterator it;
		for (it = particles.begin(); it != particles.end(); ++it)
		{
			it->render();
		}
		glEnd();
	}
};


std::list<ParticleSystem> psystems;


// Number of seconds between frame updates
const float FRAME_PERIOD = 0.25;


// Used to approximate the time between updates
int currentTime = 0;
int previousTime = 0;


// A time accumulator for determining when to render the next frame
float elapsed = 0.0;


void GLrender();
void GLupdate();


void myMouse(int button, int state, int x, int y){


	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN){
			Point2D t = GLscreenToWindowCoordinate(Point2D(x, y));
			Vector3 temp;
			temp.x = t.x;
			temp.y = t.y;
			temp.z = 0;
			ParticleSystem newSystem(temp);
			psystems.push_back(newSystem);
			glutPostRedisplay();
		}
	}


}


//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Lab 9 - Hui Yang");
	glutMouseFunc(myMouse);
	glutDisplayFunc(GLrender);
	glutIdleFunc(GLupdate);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glOrtho(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, VIEW_NEAR, VIEW_FAR);
}


int main(int argc, char** argv)
{
	GLInit(&argc, argv);
	glutMainLoop();
	return 0;
}


void GLupdate()
{
	// Update time elapsed
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int diffTime = currentTime - previousTime;
	previousTime = currentTime;


	elapsed += (diffTime / 1000.0);


	// See if the accumulated elapsed time is enough render the next frame. 
	if (elapsed > FRAME_PERIOD)
	{
		std::list<ParticleSystem>::iterator it;


		// Update all existed particle systems
		for (it = psystems.begin(); it != psystems.end(); ++it)
		{
			it->update(elapsed);
		}


		// Clean up all empty (inactive) particle sytems
		for (it = psystems.begin(); it != psystems.end();)
		{
			if (it->isEmpty())
				it = psystems.erase(it);
			else
				++it;
		}


		glutPostRedisplay();
		elapsed = 0;
	}
}


void GLrender()
{
	glClear(GL_COLOR_BUFFER_BIT);


	// Render all particle systems 
	std::list<ParticleSystem>::iterator it;
	for (it = psystems.begin(); it != psystems.end(); ++it)
	{
		it->render();
	}


	glFlush();
	glutSwapBuffers();
}
