#pragma once

#include "dictionary.h"

size_t FindDelim(const std::string& str, size_t begPos = 0);

class CheckingText
{
private:
    Dictionary dict;

    std::string CheckWord(const std::string& word);
public:
    CheckingText() = default;
    CheckingText(const Dictionary& _dict) : dict(_dict) {}

    void SetDict(const Dictionary& _dict)
    {
        dict = _dict;
    }

    void ReadDict(const std::string& filename);

    void Check(const std::string& fileInput = "input", const std::string& fileOutput = "output", const std::string& fileNewDict = "new_dict");
};
