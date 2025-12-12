/*
    Group: Terek Johnson – tjohn108 – Session 023, Oscar La – ola002 – Session 021
        - DatasetID: titanic-clean.txt
        - Small Dataset Results:
        - Forward: Feature Subset: {3, 5}, Acc: 92%
        - Backward: Feature Subset: <your best feature subset>, Acc:<your acc. on that feature subset>
        - Large Dataset Results:
        - Forward: Feature Subset: <your best feature subset>, Acc: <your accuracy on that feature subse
*/
#include "selection.h"
#include "elimination.h"
#include "validation.h"

#include <string>


int main(int argc, char const *argv[])
{


    std::cout << "Welcome to Oscar's and Terek's Feature Selection algorithm" << std::endl << std::endl;

    std::cout << "Enter the file path of your dataset: ";

    std::string filePath;
    std::cin >> filePath;


    std::cout << std::endl << std::endl 
    << "Type the number of the algorithm you want to run." << std::endl
    << "    1) Forward Selection Algorithm" << std::endl 
    << "    2) Backward Elimination Algorithm" << std::endl << std::endl;

    int algorithmSelection = 0;
    int featureCount;
    
    std::cin >> algorithmSelection;

    
    if (algorithmSelection == 1 || algorithmSelection) {
        switch (algorithmSelection) {
            case 1:
                std::cout << std::endl << "Running Forward Selection Algorithm:" << std::endl << std::endl;
                forwardSelection(filePath);
                break;
            case 2:
                std::cout << std::endl << "Running Backward Elimination Algorithm:" << std::endl << std::endl;
                if(filePath == "fast.txt") backTracing(filePath, 10);
                else if(filePath == "large.txt") backTracing(filePath, 40);
                else backTracing(filePath, 6);
                break;
            default:
                break;
        }
    } else {
        std::cout << "You entered an invalid selection. Please run the program again!";
    }
    return 0;
}
