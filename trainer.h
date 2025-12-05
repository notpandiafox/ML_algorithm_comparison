#include <vector>
#include <fstream>
#include <string>
#include <cmath>

float calculateEuclideanDistance(Datapoint, Datapoint, std::vector<int>);

struct Datapoint { 
    const std::vector<float> features;
    const int classLabel;
    const int trainingSetIdx;

    
    Datapoint(const std::vector<float> &features, int classLabel, int trainingSetIdx):
        features(features),
        classLabel(classLabel),
        trainingSetIdx(trainingSetIdx)
        {}

    int getTrainingSetIdx() { return trainingSetIdx; }
    int getClassLabel() { return classLabel; }
    float getFeatureByIndex(int idx) { return features.at(idx); }
};

struct Trainer {
    const std::vector<Datapoint> trainingSet;

    Trainer(std::string filePath) : trainingSet(loadTrainingSet(filePath)) {};


    int test(Datapoint testPoint, std::vector<int> featureIndices) {
        int predictedLabel = -1;
        float closestDistance; 
        float calculatedDistance;
        for (Datapoint comparisonPoint : trainingSet) {
            if (testPoint.getTrainingSetIdx() == comparisonPoint.getTrainingSetIdx()) { continue; }
            calculatedDistance = calculateEuclideanDistance(testPoint, comparisonPoint, featureIndices);
            if (calculatedDistance < closestDistance) {
                closestDistance = calculatedDistance;
                predictedLabel = comparisonPoint.getClassLabel();
            }
        }
    }

    private:

        std::vector<Datapoint> loadTrainingSet(std::string filePath) {
            std::ifstream file{filePath};

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
                        nextClassLabel = val;
                        break;
                    }
                    features.push_back(val);
                }

                Datapoint newPoint(features, prevClassLabel, i);
                i++;
                trainingSet.push_back(newPoint);
            }

            return trainingSet;
        }

};

float calculateEuclideanDistance(Datapoint a, Datapoint b,  std::vector<int> featureIndices) {
    float sum;
    float delta;
    for (int idx : featureIndices) {
        delta = a.getFeatureByIndex(idx) - b.getFeatureByIndex(idx);
        sum += pow(delta, 2);
    }
    return sqrt(sum);
}
