// Name: 
// Quarter, Year: 
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <complex>
#include "color.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

Color3d mycolor(1.0, 1.0, 1.0);

// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 0.0)
{
// ...
// Complete this function
    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex2f(x, y);
    glEnd();
// ...
}


void renderJuliaSet(double xmin,double xmax,double ymin,double ymax)
{
    //x*x+(-0.7795+0.134i)
	const int MAX_ITERS = 100;

        for(int a=0;a<=WINDOW_WIDTH; ++a)
        {
           for(int b=0; b<=WINDOW_HEIGHT; ++b)
           {
          	    int iters=0;
    	        double getreal = (a)/800.0*(xmax-xmin) +xmin;
                double getimg = (b)/800.0 *(ymax-ymin) +ymin;
           	    std::complex<double>val(getreal, getimg);
           	    std::complex<double>plus(-0.7795 ,0.134);
                //or std::complex<double>plus(-0.59 ,0);
    			    while(std::abs(val) <2.0 && iters <MAX_ITERS)
    			    {
    			      val = val*val+plus; //or val=exp(val*val*val)+plus
    		           ++iters;
    			    }
                mycolor.rotateHue(iters);
                renderPixel(a, b,mycolor.r,mycolor.g, mycolor.b);
            }
        }      
}


void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);      
    renderJuliaSet(-2.0,2.0,-2.0,2.0);      
    glutSwapBuffers();
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
      
    // ...
    // Complete this function
    // ...
    glutCreateWindow("CS 130 - Hui Yang");
    glutDisplayFunc(GL_render);
    // The default view coordinates is (-1.0, -1.0) bottom left & (1.0, 1.0) top right.
    // For the purposes of this lab, this is set to the number of pixels
    // in each dimension.
    glMatrixMode(GL_PROJECTION_MATRIX);
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
}

int main(int argc, char** argv)
{    
    GLInit(&argc, argv);
    glutMainLoop();

    return 0;
}


