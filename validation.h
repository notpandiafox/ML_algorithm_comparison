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

        std::cout << "Running LOOCV on dataset from file " << filePath << "..." << std::endl << std::endl;
        int i = 1;
        for (Datapoint entry : model.getTrainingSet()) {
            int prediction = model.test(entry, featureIndices);
            int actual = entry.getClassLabel();
            if (prediction == actual) {
                accuratePredictionCounter++;
                std::cout << "Entry #" << i << ") SUCCESS!" << std::endl;
            } else {
                std::cout << "Entry #" << i << ") FAIL! [" << prediction << "|" << actual << "]" << std::endl;
            }
            i++;
        }

        accuracy = accuratePredictionCounter / totalDatapoints;

        std::cout << "LOOCV using features: {";
        for (int idx : featureIndices) {
            std::cout << idx << " ";
        }
        std::cout << "} has an accuracy of " << accuracy * 100 << "%" << std::endl << std::endl;
        return accuracy;
    }

    private:



};