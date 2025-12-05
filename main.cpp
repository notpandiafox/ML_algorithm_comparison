#include "selection.h"
#include "elimination.h"
#include "validation.h"

#include <string>

std::vector<std::vector<double>> data {
    {1,0,0,1,0},
    {0,1,1,0,1},
    {1,1,1,1,1},
    {0,1,1,1,0},
    {1,1,0,0,1}
};


int main(int argc, char const *argv[])
{


    std::cout << "Welcome to Oscar's and Terek's Training and Validation Traces" << std::endl << std::endl;

    std::cout << "Enter the file path of your dataset: ";

    std::string filePath;

    std::vector<int> indicesSubSet;

    float tmp;

    Validation valid;

    std::cin >> filePath;

    std::cout << "Enter the feature subset (as indices, separated by spaces) (if done -1) : ";

    while(std::cin >> tmp)
    {
        if(tmp == -1)
            break;

        indicesSubSet.push_back(tmp - 1);
    }

    valid.valid(indicesSubSet, filePath);

    std::cout << "Trace Complete... ";




    // std::cout << "Welcome to Oscar's and Terek's Feature Selection algorithm" << std::endl << std::endl;

    // std::cout << "Type the number of the algorithm you want to run." << std::endl
    // << "    1) Forward Selection Algorithm" << std::endl 
    // << "    2) Backward Elimination Algorithm" << std::endl
    // << "    3) Oscar's and Terek's Special Algorithm" << std::endl << std::endl;

    // int algorithmSelection = 0;
    // std::vector<std::function<bool(const std::vector<double>)>> fctFuncts = {&ft1, &ft2, &ft3, &ft4};
    
    // std::cin >> algorithmSelection;
    
    // if (algorithmSelection == 1 || algorithmSelection == 2 || algorithmSelection == 3) {
    //     switch (algorithmSelection) {
    //         case 1:
    //             std::cout << std::endl << "Running Forward Selection Algorithm:" << std::endl << std::endl;
    //             forwardSelection(data, fctFuncts);
    //             break;
    //         case 2:
    //             std::cout << std::endl << "Running Backward Elimination Algorithm:" << std::endl << std::endl;
    //             backTracing(data, 4);
    //             break;
    //         case 3:
    //             std::cout << std::endl << "Running Oscar's and Terek's Special Algorithm:" << std::endl << std::endl;
    //             break;
    //         default:
    //             break;
    //     }
    // } else {
    //     std::cout << "You entered an invalid selection. Please run the program again!";
    // }
    return 0;
}
