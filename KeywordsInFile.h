#ifndef KEYWORDSINFILE_H
#define KEYWORDSINFILE_H

#include <fstream>
#include <iostream>
#include <unordered_map>

class KeywordsInFile {
private:
    std::unordered_map<std::string, int> keywords;
    std::unordered_map<int, std::unordered_map<std::string, int>> keywords_in_line;
public:
    KeywordsInFile() = delete;
    KeywordsInFile(const std::string &filename_with_keywords, const std::string &filename_with_text);
    bool KeywordFound(const std::string &keyword) const;
    int KeywordInLine(const std::string &keyword, const int &line_number) const;
    int TotalOccurrences(const std::string &keyword) const;

    friend std::ostream& operator<<(std::ostream &os, const KeywordsInFile &kif);
};


#endif //KEYWORDSINFILE_H
