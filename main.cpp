#include <vector>
#include <functional>
#include <random>

#include "Selection.h"

std::vector<std::vector<double>> data {
    {1,0,0,1,0},
    {0,1,1,0,1},
    {1,1,1,1,1},
    {0,1,1,1,0},
    {1,1,0,0,1}
};

bool getGroundTruth(std::vector<double>);

bool getEstimate(std::vector<double>, std::vector<bool>);

bool ft1(std::vector<double> dataPoint) {
    return (dataPoint.at(1) == 1);
}
bool ft2(std::vector<double> dataPoint) {
    return (dataPoint.at(2) == 1);
}
bool ft3(std::vector<double> dataPoint) {
    return (dataPoint.at(3) == 1);
}
bool ft4(std::vector<double> dataPoint) {
    return (dataPoint.at(4) == 1);
}

int main(int argc, char const *argv[])
{   
    std::vector<std::function<bool(const std::vector<double>)>> ftFuncts = {&ft1, &ft2, &ft3, &ft4};
    forwardSelection(data, ftFuncts);
    return 0;
}

bool getGroundTruth(std::vector<double> dataPoint) { return dataPoint.at(0) == 1; }


//ListFeatureFunction is an array of functions so treat them as such
// bool getEstimate(const std::vector<double>& dataPoint,
//                  const std::vector<std::function<bool(const std::vector<double>)>>& listFeatureFunctions)
// {
//     std::vector<bool> guesses;

//     for (auto& ft : listFeatureFunctions)
//     {
//         guesses.push_back(ft(dataPoint));
//     }

//     return guesses.at(rand() % guesses.size());
// }

