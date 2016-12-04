
How to set the training data set different from the testing?

I had a first try but failed...

Carmen told me the reason:

I should create a trainingtestdataset.java, using the similiar code..

number of ngrams = 4096 for more_data/

number of ngrams = 3704 for data/

This will incur vector dimensions not match, so I add two things:


### Reuse generalFrequencies from the training data:

add in NavieBayesClassifier.java:

```java
   PreparingTrainingDataSet a = new PreparingTrainingDataSet();
   ArrayList<ArrayList<Double>> trainingSet = a.run();
   Hashtable<String,Integer> usefulTable= a.generalFrequencies;

   testing dataset is sperated from training dataset
   PreparingTestingDataSet b = new PreparingTestingDataSet(usefulTable);
   ArrayList<ArrayList<Double>> testingSet = b.run();
```


### Preserve the keysets of generalFrequencies from the training data:

```java
  // preserver the keySets form the generalFrequencies from training data
		generalFrequencies = (Hashtable)usefulTable.clone();
		for(String key: generalFrequencies.keySet()){
			generalFrequencies.put(key, 0);
		}

```

### Discard features not appeared in the trainning data:

 ```java
    // added by Hui
    // ignore features not included in training data
    if( usefulTable.keySet().contains(newString) ){
     if(systemCallTraceFreq.containsKey(newString)){
      systemCallTraceFreq.put(newString, systemCallTraceFreq.get(newString)+1);
     }else{
      systemCallTraceFreq.put(newString, 1);	



       if(generalFrequencies.containsKey(newString) ){
        generalFrequencies.put(newString, generalFrequencies.get(newString)+1);
       }else{
        generalFrequencies.put(newString, 1);	
       }

     }
    }
 ```

