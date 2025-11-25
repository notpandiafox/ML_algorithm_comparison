#include <vector>
#include <iostream>
#include <string>
#include "helper.h"
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

int classAUsingFeatures(std::vector<std::vector<double>> dataset, std::vector<std::function<bool(const std::vector<double>)>>& ftFunctions) {
    int classA = 0;
    for (std::vector<double> datapoint : dataset) {
        if (getEstimateT(datapoint, ftFunctions) == getGroundTruth(datapoint)) classA++;
    }
    return classA;
}
void forwardSelection(const std::vector<std::vector<double>>& dataset, const std::vector<std::function<bool(const std::vector<double>)>> allFeatures)
{
    std::vector<std::function<bool(const std::vector<double>)>> bestFeatures;
    std::vector<int> unusedFeatures;
    std::vector<int> usedFeatures;
    std::vector<int> selectedFeatures;

    for (int i = 0; i < allFeatures.size(); i++) {
        unusedFeatures.push_back(i);
    }
    std::cout << "Beginning search!" << std::endl;

    int initialEstimate = 0;
    for (std::vector<double> datapoint : dataset) {
        if (getGroundTruth(datapoint)) initialEstimate++;
    }
    double bestAccuracy = (double) initialEstimate / dataset.size();
    std::cout << "Using no features and 'random' evaluation, I get an accuracy of " << bestAccuracy * 100.0 << "%" << std::endl;


    while (!unusedFeatures.empty()) {
        double tempAccuracy = 0.0;
        int bestFeature = -1;

        for (int ft : unusedFeatures) {
            std::vector<std::function<bool(const std::vector<double>)>> trialFeatures = bestFeatures;
            trialFeatures.push_back(allFeatures[ft]);

            int tracked = classAUsingFeatures(dataset, trialFeatures);
            double calcAccuracy = (double) tracked / dataset.size();

            if (calcAccuracy > tempAccuracy) {
                tempAccuracy = calcAccuracy;
                bestFeature = ft;
            }
            
            // print: Using feature(s) {1,2} accuracy is 58.9%
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

        if ((tempAccuracy > bestAccuracy) && (bestFeature != -1)) {
            selectedFeatures.push_back(bestFeature);
            bestFeatures.push_back(allFeatures[bestFeature]);
            bestAccuracy = tempAccuracy;
            std::cout << "Feature set " << ftsToString(usedFeatures) << " was best, accuracy is " << bestAccuracy * 100.0 << "%" << std::endl << std::endl;
        }
        if ((tempAccuracy <= bestAccuracy && (bestFeature != -1))) {
            std::cout << "(Warning, Accuracy has decreased!)" << std::endl;
            // break;
        }
    }
    // print: Finished search!! The best feature subset is {4,1,2}, which has an accuracy of 76.4%
    std::cout << std::endl << "Finished search!! The best feature subset is " << ftsToString(selectedFeatures) << ", which has an accuracy of " << bestAccuracy * 100.0 << "%" << std::endl;
}