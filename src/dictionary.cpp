#include <algorithm>
#include "dictionary.h"

bool Dictionary::ContainsWord(const std::string& word) const
{
    return dict.contains(word);
}

void Dictionary::ContainsWordErrChar(const std::string& word, char c, std::set<std::string>& res) const
{
    std::string buff = word;

    for (size_t i{}; i < word.length(); ++i)
    {
        if (c == ' ')
        {
            buff.erase(i, 1);

            if (ContainsWord(buff))
                res.insert(buff);

            buff.insert(i, 1, word[i]);
        }
        else
        {
            buff[i] = c;

            if (ContainsWord(buff))
                res.insert(buff);

            buff[i] = word[i];
            buff.insert(i, 1, c);

            if (ContainsWord(buff))
                res.insert(buff);

            buff.erase(i, 1);
        }
    }

    if (ContainsWord(buff.insert(buff.length(), 1, c)))
        res.insert(buff);
}

std::vector<std::string> Dictionary::GetSimilarWords(const std::string& word) const
{
    std::set<std::string> resSet;

    for (char c{'a'}; c <= 'z'; ++c)
        ContainsWordErrChar(word, c, resSet);

    for (char c{'A'}; c <= 'Z'; ++c)
        ContainsWordErrChar(word, c, resSet);

    ContainsWordErrChar(word, ' ', resSet);

    std::vector<std::string> res(resSet.begin(), resSet.end());

    return res;
}

void Dictionary::AddWord(const std::string word)
{
    dict.insert(word);
}

std::istream& operator>>(std::istream& in, Dictionary& dict)
{
    std::string buff;

    while (in >> buff)
        dict.AddWord(buff);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Dictionary& dict)
{
    std::for_each(dict.dict.begin(), dict.dict.end(), [&out](const std::string& word)
    {
        out << word << "\n";
    });

    return out;
}