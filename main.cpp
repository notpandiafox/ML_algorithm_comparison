#include "selection.h"
#include "elimation.h"

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
    return 0;
}
