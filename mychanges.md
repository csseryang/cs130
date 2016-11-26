In classifiers.java, use this to generate a sample_array.txt:
```java
package helloworld;
import java.util.ArrayList;

public class Classifiers {
	public static void main(String[] args) {
		PreparingTrainingDataSet a = new PreparingTrainingDataSet();
		ArrayList<ArrayList<Double>> trainingSet = a.run();
		
		int i=0;
		for(ArrayList<Double> innerList : trainingSet) {
		    for(Double number : innerList) {
		        System.out.print(number+",");
		       
		    }
		    if(i==0)
	        	System.out.print("benigh");
	        else 
	        	System.out.print("malware");
	        
		    System.out.println();
		    i++;
		}
	}

}
```

transfer this csv to arff format by [link](http://ikuz.eu/csv2arff/)

Then modity classifiers.java 
```java
package helloworld;
import java.io.File;
import java.util.ArrayList;

import jsat.ARFFLoader;
import jsat.DataSet;
import jsat.classifiers.CategoricalResults;
import jsat.classifiers.ClassificationDataSet;
import jsat.classifiers.Classifier;
import jsat.classifiers.DataPoint;
import jsat.classifiers.bayesian.NaiveBayes;

public class Classifiers {
	public static void main(String[] args) {
//		PreparingTrainingDataSet a = new PreparingTrainingDataSet();
//		ArrayList<ArrayList<Double>> trainingSet = a.run();
		
//		int i=0;
//		for(ArrayList<Double> innerList : trainingSet) {
//		    for(Double number : innerList) {
//		        System.out.print(number+",");
//		       
//		    }
//		    if(i==0)
//	        	System.out.print("benigh");
//	        else 
//	        	System.out.print("malware");
//	        
//		    System.out.println();
//		    i++;
//		}
		File file = new File( "/Users/hyang027/Downloads/sample_array.txt");

        DataSet dataSet = ARFFLoader.loadArffFile(file);
      //We specify '0' as the class we would like to make the target class. 
        ClassificationDataSet cDataSet = new ClassificationDataSet(dataSet, 0);

        int errors = 0;
        Classifier classifier = new NaiveBayes();
        classifier.trainC(cDataSet);

        for(int i = 0; i < dataSet.getSampleSize(); i++)
        {
            DataPoint dataPoint = cDataSet.getDataPoint(i);//It is important not to mix these up, the class has been removed from data points in 'cDataSet' 
            int truth = cDataSet.getDataPointCategory(i);//We can grab the true category from the data set

            //Categorical Results contains the probability estimates for each possible target class value. 
            //Classifiers that do not support probability estimates will mark its prediction with total confidence. 
            CategoricalResults predictionResults = classifier.classify(dataPoint);
            int predicted = predictionResults.mostLikely();
            if(predicted != truth)
                errors++;
            System.out.println( i + "| True Class: " + truth + ", Predicted: " + predicted + ", Confidence: " + predictionResults.getProb(predicted) );
        }

        System.out.println(errors + " errors were made, " + 100.0*errors/dataSet.getSampleSize() + "% error rate" );
	}

}
```
