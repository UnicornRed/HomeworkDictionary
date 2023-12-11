#include <iostream>
#include "checkingText.h"

int main(int argc, char* argv[])
{
    std::string fileInput, fileOutput, fileDict, fileNewDict;

    fileInput = argc > 1 ? argv[1] : "input";
    fileDict = argc > 2 ? argv[2] : "dict";
    fileOutput = argc > 3 ? argv[3] : "output";
    fileNewDict = argc > 4 ? argv[4] : "new_dict";

    CheckingText chT;

    try
    {
        chT.ReadDict(fileDict);
        chT.Check(fileInput, fileOutput, fileNewDict);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Try: ./Dictionary [input] [dictionary] [output] [new_dict].\n";

        return 1;
    }

    return 0;
}