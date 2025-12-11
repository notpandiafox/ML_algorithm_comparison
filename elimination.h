#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <cmath>

#include "helper.h"
#include "validation.h"

void backTracing(std::string file, int);
void initializeBestFeatures(std::vector<int>& bestSetOfFeatures, int amountOfFeatures);
double findScoreOfSet(std::vector<std::vector<double>>&, std::vector<int>&);
void printFeatures(std::vector<int> set, double score);
void printBestFeature(std::vector<int> set, double score);
bool setEmpty(std::vector<int> set);
void copyVectorNoNeg(std::vector<int>&, std::vector<int>&);

void backTracing(std::string file, int amountOfFeatures)
{
    //assume that 0 is empty and 1 is 1, 2 is 2 etc.
    std::vector<int> bestSetOfFeatures;
    std::vector<int> localBestSetOfFeatures;
    std::vector<int> tmpLastSetOfFeatures;
    std::vector<int> tmpSetOfFeatures;

    Validation validator;

    double bestScore{0};
    double localBestScore{0};
    double tmpScore{0};

    bool skipGetScore{false};

    initializeBestFeatures(tmpLastSetOfFeatures, amountOfFeatures);

    bestScore = validator.valid(tmpLastSetOfFeatures, file);

    printBestFeature(tmpLastSetOfFeatures, bestScore);


    //if -1 then it has already been eliminated
    for(int i = 0; i < amountOfFeatures; ++i)
    {
        std::vector<int> validVector;

        tmpSetOfFeatures = tmpLastSetOfFeatures;    

        for(int j = 0; j < tmpLastSetOfFeatures.size(); ++j)// j is the one we temporarily elim
        {
            std::vector<int> validVector;

            if(tmpSetOfFeatures.at(j) == -1 || setEmpty(tmpSetOfFeatures))
            {
                continue;
            }

            tmpSetOfFeatures[j] = -1;

            copyVectorNoNeg(validVector, tmpSetOfFeatures);

            tmpScore = validator.valid(validVector, file); //tmpSetOfFeatures

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
            std::cout << bestSetOfFeatures.at(i) + 1 << ",";
        }
    }

    std::cout << "} , which has an accuracy of " << bestScore * 100.0 << "%" << std::endl;;

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

void copyVectorNoNeg(std::vector<int>& copyVector, std::vector<int>& OGvector)
{
    for(int stuffInVector : OGvector)
    {
        if(stuffInVector == -1)
            continue;
        
        copyVector.push_back(stuffInVector);
    }
}

void initializeBestFeatures(std::vector<int>& bestSetOfFeatures, int amountOfFeatures)
{
    for(int i = 0; i < amountOfFeatures; ++i)
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

    std::cout << "} accuracy is " << score * 100.0 << "%" << std::endl;

}

void printBestFeature(std::vector<int> set, double score)
{
    std::cout << "Feature set {";
    for(int num : set)
    {
        if(num != -1)
            std::cout << num << ",";
    }   
    std::cout << "} was best, accuracy  is " << score * 100.0 << "%" << std::endl;
    std::cout << std::endl;
}
