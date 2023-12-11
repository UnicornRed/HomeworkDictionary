#include <fstream>
#include <algorithm>
#include <limits>
#include "checkingText.h"

constexpr char messageUnknown[] ="An unknown word: ";

constexpr char messageSelect[] = "Select an action option:\n"
                                  "1 - Add a word to the dictionary;\n"
                                  "2 - Leave it in the text, but do not add it to the dictionary;\n";

constexpr char messageReplace[] = "3 - Replace with another word:\n";

size_t FindDelim(const std::string& str, size_t begPos)
{
    for (size_t i{begPos}; i < str.length(); ++i)
        if (!std::isalpha(str[i]))
            return i;

    return std::string::npos;
}

void CheckingText::ReadDict(const std::string& filename)
{
    std::ifstream in(filename);

    if (!in.is_open())
        throw std::ios_base::failure("Error filename of dictionary! Dictionary " + filename + " was not open");

    in >> dict;

    in.close();
}

std::string CheckingText::CheckWord(const std::string& word)
{
    if (dict.ContainsWord(word))
        return word;

    std::string option;
    std::vector<std::string> similarWords = dict.GetSimilarWords(word);

    std::cout << messageUnknown << word << "\n" << messageSelect;
    
    if (similarWords.size() > 0)
    {
        std::cout << messageReplace;
        
        for (size_t i{}; i < similarWords.size(); ++i)
            std::cout << "\t" << i + 1 << ". " + similarWords[i] << "\n";
    }

    while (std::cin >> option)
    {
        if (option.length() > 1)
            option = "?";

        switch (option[0])
        {
        case '1':
            dict.AddWord(word);
            return word;
        
        case '2':
            return word;

        case '3':
            if (similarWords.size() > 0)
            {
                size_t num;

                while (true)
                {
                    std::cout << "Input the number of word for replace: ";

                    std::cin >> num;

                    if (num > similarWords.size())
                        std::cout << "Error! Incorrect the number of word. It must be less or equal " << similarWords.size() << ".\n";
                    else
                        return similarWords[num - 1];
                }

            }

        default:
            std::cout << "Error! Enter the correct item number.\n";

            break;
        }
    }

    return "";
}

void CheckingText::Check(const std::string& fileInput, const std::string& fileOutput, const std::string& fileNewDict)
{
    std::ifstream in(fileInput);

    if (!in.is_open())
        throw std::ios_base::failure("Error input filename! File " + fileInput + " was not open");

    std::ofstream out(fileOutput);

    if (!out.is_open())
        throw std::ios_base::failure("Error output filename! File " + fileOutput + " was not open");

    std::ofstream outNewDict(fileNewDict);

    if (!outNewDict.is_open())
        throw std::ios_base::failure("Error filename of new dictionary! File " + fileNewDict + " was not open");

    std::string buff, word;
    size_t pos1, pos2;

    while (std::getline(in, buff))
    {
        pos2 = pos1 = 0;

        while (pos2 != std::string::npos)
        {
            while (pos1 < buff.length() && !std::isalpha(buff[pos1]))
                ++pos1;
            out << buff.substr(pos2, pos1 - pos2);

            pos2 = FindDelim(buff, pos1);

            word = buff.substr(pos1, pos2 == std::string::npos ? std::string::npos : pos2 - pos1);

            if (word != "")
                out << CheckWord(word);

            pos1 = pos2;
        }

        out << "\n";
    }

    outNewDict << dict;

    outNewDict.close();
    out.close();
    in.close();
}