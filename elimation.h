#ifndef ELIMATION_H
#define ELIMATION_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <cmath>

#include "helper.h"

void backTracing(std::vector<std::vector<double>> data);
void initializeBestFeatures(std::vector<int>& bestSetOfFeatures, int amountOfFeatures);
double findScoreOfSet(std::vector<std::vector<double>>&, std::vector<int>&);
void printFeatures(std::vector<int> set, double score);
void printBestFeature(std::vector<int> set, double score);
bool setEmpty(std::vector<int> set);

void backTracing(std::vector<std::vector<double>>& data, int amountOfFeatures)
{
    //assume that 0 is empty and 1 is 1, 2 is 2 etc.
    std::vector<int> bestSetOfFeatures;
    std::vector<int> localBestSetOfFeatures;
    std::vector<int> tmpLastSetOfFeatures;
    std::vector<int> tmpSetOfFeatures;

    std::unordered_map<int,int> whatHasBeenEliminated;

    double bestScore{0};
    double localBestScore{0};
    double tmpScore{0};

    bool skipGetScore{false};

    initializeBestFeatures(tmpLastSetOfFeatures, amountOfFeatures);

    bestScore = findScoreOfSet(data, tmpLastSetOfFeatures);

    printBestFeature(tmpLastSetOfFeatures, bestScore);


    //if -1 then it has already been eliminated
    for(int i = 0; i < data.size(); ++i)
    {
        tmpSetOfFeatures = tmpLastSetOfFeatures;    

        for(int j = 1; j <= amountOfFeatures; ++j)// j is the one we temporarily elim
        {
            if(tmpSetOfFeatures.at(j) == -1 || setEmpty(tmpSetOfFeatures))
            {
                continue;
            }

            tmpSetOfFeatures[j] = -1;


            tmpScore = findScoreOfSet(data, tmpSetOfFeatures);

            printFeatures(tmpSetOfFeatures, tmpScore);

            if(tmpScore > localBestScore)
            {
                localBestScore = tmpScore;
                localBestSetOfFeatures = tmpSetOfFeatures;
            }

            tmpSetOfFeatures = tmpLastSetOfFeatures;
        }

        if(localBestScore >= bestScore)
        {
            printBestFeature(localBestSetOfFeatures, localBestScore);
            bestScore = localBestScore;
            bestSetOfFeatures = localBestSetOfFeatures;
        }
        else if(localBestScore < bestScore)
        {
            std::cout << "(Warning, Accuracy Decreased!)" << std::endl;
            break;
        }
        localBestScore = 0;
        tmpLastSetOfFeatures = localBestSetOfFeatures;
    }

    std::cout << "Finished search!! The best feature subset is {";
     
    for(int i = 1; i < bestSetOfFeatures.size(); ++i)
    {
        if(bestSetOfFeatures.at(i) != -1)
        {
            std::cout << bestSetOfFeatures.at(i) << ",";
        }
    }

    std::cout << "} , which has an accuracy of " << bestScore << "%" << std::endl;;

}

bool setEmpty(std::vector<int> set)
{
    for(int num : set)
    {
        if(num != -1)
            return false;
    }

    return true;
}

void initializeBestFeatures(std::vector<int>& bestSetOfFeatures, int amountOfFeatures)
{
    bestSetOfFeatures.push_back(-1);

    for(int i = 1; i < amountOfFeatures + 1; ++i)
    {
        bestSetOfFeatures.push_back(i);
    }
}

double findScoreOfSet(std::vector<std::vector<double>>& data, std::vector<int>& set)
{
    std::vector<bool> predictions;
    double predict{};

    for(int i = 0; i < data.size(); ++i)
    {
        if(getEstimate(data.at(i), set) == getGroundTruth(data.at(i)))
        {
            ++predict;
        }
    }

    double percentage = (predict / (double)data.size()) * 100.0;

    return std::round(percentage * 10.0) / 10.0;;
}

void printFeatures(std::vector<int> set, double score)
{
    std::cout << "Using feature(s) {";
    for(int num : set)
    {
        if(num != -1)
            std::cout << num << ",";
    }   

    std::cout << "} accuracy is " << score << "%" << std::endl;

}

void printBestFeature(std::vector<int> set, double score)
{
    std::cout << "Feature set {";
    for(int num : set)
    {
        if(num != -1)
            std::cout << num << ",";
    }   
    std::cout << "} was best, accuracy  is " << score << "%" << std::endl;
    std::cout << std::endl;
}


#endif