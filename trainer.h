
#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>

#define CLASSA_LABEL 0.0f
#define CLASSB_LABEL 1.0f
#define FEATURE_COUNT 6

// Datapoint class for representing entries in our dataset, with helpers to get relevant info (feature, index, label, etc.)
struct Datapoint { 
    const std::vector<float> features;
    const int classLabel;
    const int trainingSetIdx;

    
    Datapoint(const std::vector<float> &features, int classLabel, int trainingSetIdx):
        features(features),
        classLabel(classLabel),
        trainingSetIdx(trainingSetIdx)
        {}

    std::vector<float> getFeatures() { return features; }
    int getTrainingSetIdx() { return trainingSetIdx; }
    int getClassLabel() { return classLabel; }
    float getFeatureByIndex(int idx) { return features.at(idx); }
};

// Calculates the euclidean distance between two Datapoints given a set of features.
float calculateEuclideanDistance(Datapoint a, Datapoint b,  std::vector<int> featureIndices) {
    float sum = 0.0f;
    float delta;
    for (int idx : featureIndices) {
        delta = a.getFeatureByIndex(idx) - b.getFeatureByIndex(idx);
        sum += delta * delta;
    }
    return sqrt(sum);
}

// Trainer represents the training dataset and test methods.
struct Trainer {
    const std::vector<Datapoint> trainingSet;

    Trainer(std::string filePath) : trainingSet(loadTrainingSet(filePath)) {};

    
    std::vector<Datapoint> getTrainingSet() { return trainingSet; }
    
    // Test method returns our model's predicted label using 1-NN algorithm
    int test(Datapoint testPoint, std::vector<int> featureIndices) {
        int predictedLabel = -1;
        float closestDistance = -1.0f; 
        float calculatedDistance = 0;
        for (Datapoint comparisonPoint : trainingSet) {
            if (testPoint.getTrainingSetIdx() == comparisonPoint.getTrainingSetIdx()) { continue; }
            calculatedDistance = calculateEuclideanDistance(testPoint, comparisonPoint, featureIndices);
            if ((calculatedDistance < closestDistance) || (closestDistance < 0)) {
                closestDistance = calculatedDistance;
                predictedLabel = comparisonPoint.getClassLabel();
            }
        }
        return predictedLabel;
    }

    private:

        // loadTrainingSet handles file stream to retrieve dataset entries, initiating each entry as a Datapoint 
        std::vector<Datapoint> loadTrainingSet(std::string filePath) {
            std::ifstream file{filePath};

            if (!file) {
                throw("File not found!");
            }
            int i = 0;
            std::vector<Datapoint> trainingSet;
            float val;
            float classLabel;

            while(file >> val) {
                std::vector<float> features;
                
                classLabel = val;

                int j = 0;
                while (file >> val) {
                    features.push_back(val);
                    j++;
                    if (j >= FEATURE_COUNT) {
                        j = 0;
                        break;
                    }
                }
                Datapoint newPoint(features, classLabel, i);
                i++;
                trainingSet.push_back(newPoint);
            }

            // Before finalizing the training set, we normalize the dataset
            std::vector<Datapoint> normalizedTrainingSet = normalizeDataset(trainingSet);
            return normalizedTrainingSet;
        }


        // normalizeDataset normalizes our data entries using Z-score normalization to eliminate inaccuracies of feature selection
        std::vector<Datapoint> normalizeDataset(std::vector<Datapoint>& dataset) {

            std::vector<Datapoint> normalizedDataset;

            Datapoint sample = dataset.at(0);
            int featureCount = sample.getFeatures().size();
            
            std::vector<float> sums(featureCount);
            std::vector<float> mu(featureCount);
            std::vector<float> omega(featureCount);
            std::vector<Datapoint> normalizedTrainingSet;
            std::vector<float> sumSquaredMean(featureCount);

            
            for (Datapoint entry : dataset) {
                std::vector<float> features = entry.getFeatures();
                float tempSum = 0;
                for (int i = 0; i < features.size(); i++) {
                    // sum for ft i = sums for ft i thus far + current feature i value
                    sums[i] = sums.at(i) + features.at(i);
                }
            }
            for (int i = 0; i < mu.size(); i++) {
                 mu[i] = sums.at(i) / dataset.size();
            }


            for(Datapoint entry : dataset)
            {
                std::vector<float> features = entry.getFeatures();
                for(int i = 0; i < features.size(); ++i)
                {
                    sumSquaredMean[i] += pow(features.at(i) - mu.at(i), 2);
                }
            }
            for(int i = 0; i < sumSquaredMean.size(); ++i)
            {
                omega[i] = sqrt(sumSquaredMean.at(i)/dataset.size());

            }
            for(Datapoint entry : dataset)
            {
                std::vector<float> normalizedFeatures;
                std::vector<float> rawFeatures = entry.getFeatures();
                for(int i = 0; i < rawFeatures.size(); ++i)
                {
                    float xprime = ((rawFeatures.at(i) - mu.at(i)) / omega.at(i));
                    normalizedFeatures.push_back(xprime);
                }
                Datapoint entryNorm = Datapoint(normalizedFeatures, entry.getClassLabel(), entry.getTrainingSetIdx());
                normalizedTrainingSet.push_back(entryNorm);
            }
            return normalizedTrainingSet;
        }



};