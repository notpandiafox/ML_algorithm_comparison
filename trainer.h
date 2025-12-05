#include <vector>
#include <fstream>
#include <string>
#include <cmath>


struct Datapoint { 
    std::vector<float> features;
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
        float calculatedDistance;
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

            normalize(trainingSet);


            return trainingSet;
        }


        void normalize(std::vector<Datapoint>& data) {
            if (data.empty()) return;

            int numFeatures = data[0].features.size();

            std::vector<float> minVals(numFeatures,  std::numeric_limits<float>::infinity());
            std::vector<float> maxVals(numFeatures, -std::numeric_limits<float>::infinity());

            for (auto& point : data) {
                for (int f = 0; f < numFeatures; f++) {
                    float val = point.features[f];
                    if (val < minVals[f]) minVals[f] = val;
                    if (val > maxVals[f]) maxVals[f] = val;
                }
            }

            for (auto& point : data) {
                for (int f = 0; f < numFeatures; f++) {
                    float minv = minVals[f];
                    float maxv = maxVals[f];
                    float range = maxv - minv;

                    if (range > 0) {
                        point.features[f] = (point.features[f] - minv) / range;
                    } else {
                        point.features[f] = 0.0f;
                    }
                }
            }
        }


};

