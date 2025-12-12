#pragma once

#include <iostream>
#include "trainer.h"

class Validation
{
    public:

    // valid returns the accuracy of a subset of features given a dataset in a file
    float valid(std::vector<int> featureIndices, std::string filePath) {
        float accuracy;
        int accuratePredictionCounter = 0;
        int totalDatapoints = 0;

        Trainer model(filePath); // we use the same training set/model for LOOCV, but skip over the test subject (leaving one out)
        totalDatapoints = model.getTrainingSet().size();

        int i = 1;
        for (Datapoint entry : model.getTrainingSet()) {
            int prediction = model.test(entry, featureIndices);
            int actual = entry.getClassLabel();
            if (prediction == actual) {
                accuratePredictionCounter++;
            } else {
            }
            i++;
        }

        accuracy = (float)accuratePredictionCounter / (float)totalDatapoints;

        for (int idx : featureIndices) {
            std::cout << idx + 1 << " ";
        }

        return accuracy;
    }

    private:



};