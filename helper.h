#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <random>

bool getGroundTruth(std::vector<double> dataPoint) { return dataPoint.at(0) == 1; }


//ListFeatureFunction is an array of functions so treat them as such
bool getEstimate(const std::vector<double>& dataPoint,
                 const std::vector<std::function<bool(const std::vector<double>)>>& listFeatureFunctions)
{
    std::vector<bool> guesses;

    for (auto& ft : listFeatureFunctions)
    {
        guesses.push_back(ft(dataPoint));
    }

    return guesses.at(rand() % guesses.size());
}

bool getEstimate(const std::vector<double>& dataPoint,
                 const std::vector<int>& featureIndices)
{
    std::vector<bool> guesses;

    for (int idx : featureIndices)
    {
        if(idx != -1)    
        {
            bool featureValue = (dataPoint[idx] == 1);
            guesses.push_back(featureValue);
        }
    }

    if (guesses.empty()) {
        return false;  
    }

    return guesses.at(rand() % guesses.size());
}