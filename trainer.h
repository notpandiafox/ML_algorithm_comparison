#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>


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

float calculateEuclideanDistance(Datapoint a, Datapoint b,  std::vector<int> featureIndices) {
    float sum = 0.0f;
    float delta;
    for (int idx : featureIndices) {
        delta = a.getFeatureByIndex(idx) - b.getFeatureByIndex(idx);
        sum += delta * delta;
    }
    return sqrt(sum);
}

struct Trainer {
    const std::vector<Datapoint> trainingSet;

    Trainer(std::string filePath) : trainingSet(loadTrainingSet(filePath)) {};

    
    std::vector<Datapoint> getTrainingSet() { return trainingSet; }
    
    int test(Datapoint testPoint, std::vector<int> featureIndices) {
        int predictedLabel = -1;
        float closestDistance = -1.0f; 
        float calculatedDistance = 0;
        for (Datapoint comparisonPoint : trainingSet) {
            if (testPoint.getTrainingSetIdx() == comparisonPoint.getTrainingSetIdx()) { continue; }
            calculatedDistance = calculateEuclideanDistance(testPoint, comparisonPoint, featureIndices);
            // std::cout << calculatedDistance << " < calculated | " << closestDistance << " < closest" << std::endl;
            if ((calculatedDistance < closestDistance) || (closestDistance < 0)) {
                closestDistance = calculatedDistance;
                predictedLabel = comparisonPoint.getClassLabel();
            }
        }
        return predictedLabel;
    }

    private:

        std::vector<Datapoint> loadTrainingSet(std::string filePath) {
            std::ifstream file{filePath};

            if (!file) {
                throw("File not found!");
            }
            int i = 0;
            float prevClassLabel;
            float nextClassLabel = -1.0f;
            std::vector<Datapoint> trainingSet;
            float val;

            while(file >> val) {
                std::vector<float> features;
                if (val == 1.0f || val == 2.0f) {
                    if (nextClassLabel == -1.0f) { nextClassLabel = val; }
                    prevClassLabel = nextClassLabel;
                } else if (val != 1.0f && val != 2.0f) {
                    features.push_back(val);
                }
                
                while (file >> val) {
                    if (val == 1.0f || val == 2.0f) {
                        prevClassLabel = nextClassLabel;
                        nextClassLabel = val;
                        break;
                    }
                    features.push_back(val);
                }
                std::cout << "New datapoint: class " << prevClassLabel << std::endl;
                Datapoint newPoint(features, prevClassLabel, i);
                i++;
                trainingSet.push_back(newPoint);
            }

            std::vector<Datapoint> normalizedTrainingSet = normalizeDataset(trainingSet);


            return normalizedTrainingSet;
        }


        std::vector<Datapoint> normalizeDataset(std::vector<Datapoint>& dataset) {

            std::vector<Datapoint> normalizedDataset;

            int size = dataset.size();
            std::vector<float> sums(0);
            std::vector<float> mu(0);
            std::vector<float> omega(0);
            std::vector<Datapoint> normalizedTrainingSet;
            std::vector<float> sumSquaredMean;
            
            for (Datapoint entry : dataset) {
                std::vector<float> features = entry.getFeatures();
                for (int i = 0; i < features.size(); i++) {
                    // sum for ft i = sums for ft i thus far + current feature i value
                    sums[i] = sums.at(i) + features.at(i);
                }
                for (int i = 0; i < sums.size(); i++) {
                    mu[i] = sums.at(i) / sums.size();
                }
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
                // TODO: here?
                omega[i] = sqrt(sumSquaredMean.at(i)/dataset.size());

            }
            for(Datapoint entry : dataset)
            {
                std::vector<float> normalizedFeatures;
                std::vector<float> rawFeatures = entry.getFeatures();
                for(int i = 0; i < rawFeatures.size(); ++i)
                {
                    // TODO: HERE?
                    float xprime = ((rawFeatures.at(i) - mu.at(i)) / omega.at(i));
                    normalizedFeatures.push_back(xprime);
                }
                Datapoint entryNorm = Datapoint(normalizedFeatures, entry.getClassLabel(), entry.getTrainingSetIdx());
                normalizedTrainingSet.push_back(entryNorm);
            }
            return normalizedTrainingSet;
        }



};

