#pragma once

#include <iostream>
#include "trainer.h"

class Validation
{
    public:

    float valid(std::vector<int> featureIndices, std::string filePath) {
        float accuracy;
        int accuratePredictionCounter = 0;
        int totalDatapoints = 0;

        Trainer model(filePath);
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

        return accuracy;
    }

    private:



};