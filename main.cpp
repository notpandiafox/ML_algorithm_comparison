#include "selection.h"
#include "elimation.h"

std::vector<std::vector<double>> data {
    {1,0,0,1},
    {0,1,1,0},
    {1,1,1,1},
    {0,1,1,1},
    {1,1,0,0}
};


int main(int argc, char const *argv[])
{
    backTracing(data, 4);
    
    
    return 0;
}
