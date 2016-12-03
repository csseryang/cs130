
How to set the training data set different from the testing?

I thought something like this:

```java
 File file = new File( "/Users/hyang027/Downloads/sample_array.txt");

        File file2 = new File( "/Users/hyang027/Downloads/more_data.txt");
        DataSet dataSet = ARFFLoader.loadArffFile(file2);

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
```

But maybe just use the corssvalidation one!

Carmen told me the reason:

I should create a trainingtestdataset.java, using the same code..

number of ngrams = 4096 for more_data/

number of ngrams = 3704 for data/

This will include vector dimensions not match
