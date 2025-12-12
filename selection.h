#pragma once

#include "validation.h"

#include <vector>
#include <iostream>
#include <string>
#include "trainer.h"

// Prints integers in set notation to make it prettier
std::string ftsToString(std::vector<int>& fts) {
    if (fts.size() == 0) return "{}";
    std::string printout = "{";
    for (int ft : fts) {
        printout += std::to_string(ft + 1);
        printout += ',';
    }
    printout.back() = '}';
    return printout;
}

// Runs forward selection on a dataset
std::vector<int> forwardSelection(std::string filePath)
{
    std::vector<int> bestFeatures;
    std::vector<int> unusedFeatures;
    std::vector<int> usedFeatures;
    std::vector<int> selectedFeatures;

    // initializes untested features by considering all features
    for (int i = 0; i < FEATURE_COUNT; i++) {
        unusedFeatures.push_back(i);
    }
    std::cout << "Begingining search!" << std::endl;

    Validation valid;
   
    // tests accuracy using no features, {}
    double bestAccuracy = valid.valid({}, filePath);
    std::cout << "Using no features and 'random' evaluation, I get an accuracy of " << bestAccuracy * 100.0 << "%" << std::endl;


    // while there are features to explore, test them greedily
    while (!unusedFeatures.empty()) {
        double tempAccuracy = 0.0;
        int bestFeature = -1;

        // tests unused features concatenated with the previously discoveredd best features (empty, upon init)
        for (int ft : unusedFeatures) {
            std::vector<int> trialFeatures = bestFeatures;
            trialFeatures.push_back(ft);

            double calcAccuracy = valid.valid(trialFeatures, filePath); // runs LOOCV using feature subset

            // stores bestFeature if the current feature subset improves accuracy
            if (calcAccuracy > tempAccuracy) {
                tempAccuracy = calcAccuracy;
                bestFeature = ft;
            }
            
            std::vector<int> tempFts = usedFeatures;
            tempFts.push_back(ft);
            std::cout << "Using feature(s) " << ftsToString(tempFts) << " accuracy is " << calcAccuracy * 100.0 << "%" << std::endl << std::endl; 
        }

        usedFeatures.push_back(bestFeature);
        for (int i = 0; i < unusedFeatures.size(); i++) {
            if (unusedFeatures[i] == bestFeature) {
                unusedFeatures.erase(unusedFeatures.begin() + i);
                break;
            }
        }

        if ((tempAccuracy >= bestAccuracy) && (bestFeature != -1)) {
            selectedFeatures.push_back(bestFeature);
            bestFeatures.push_back(bestFeature);
            bestAccuracy = tempAccuracy;
            std::cout << "Feature set " << ftsToString(usedFeatures) << " was best, accuracy is " << bestAccuracy * 100.0 << "%" << std::endl;
        }
        if ((tempAccuracy < bestAccuracy && (bestFeature != -1))) {
            std::cout << "(Warning, Accuracy has decreased!)" << std::endl;
            break;
        }
    }
    
    std::cout << std::endl << std::endl << "Finished search!! The best feature subset is " << ftsToString(bestFeatures) << ", which has an accuracy of " << bestAccuracy * 100.0 << "%";
    return bestFeatures;
}