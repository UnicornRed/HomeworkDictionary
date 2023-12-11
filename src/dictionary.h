#pragma once

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <cctype>

class Dictionary
{
private:
    std::set<std::string> dict;

    void ContainsWordErrChar(const std::string& word, char c, std::set<std::string>& res) const;
public:
    Dictionary() = default;
    Dictionary(const std::vector<std::string>& words) : dict(words.begin(), words.end()) {}
    Dictionary(const std::set<std::string>& wordsSet) : dict(wordsSet.begin(), wordsSet.end()) {}

    bool ContainsWord(const std::string& word) const;

    std::vector<std::string> GetSimilarWords(const std::string& word) const;

    void AddWord(const std::string word);

    friend std::istream& operator>>(std::istream& in, Dictionary& dict);
    friend std::ostream& operator<<(std::ostream& out, const Dictionary& dict);
};

std::istream& operator>>(std::istream& in, Dictionary& dict);
std::ostream& operator<<(std::ostream& out, const Dictionary& dict);
