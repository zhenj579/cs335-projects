#include "KeywordsInFile.h"
KeywordsInFile::KeywordsInFile(const std::string &filename_with_keywords, const std::string &filename_with_text)
{
    std::ifstream file(filename_with_keywords);
    std::string word;
    while(file>>word)
    {
        keywords[word] = -1;
    }
    int line_number = 1;
    file.close();
    file.open(filename_with_text);
    while(file>>word)
    {
        if(keywords[word] == -1) keywords[word] = 1;
        else if(keywords[word] >= 1) keywords[word]++;
        if(file.peek() == '\n')
        {
            line_number++;
            continue;
        }
        keywords_in_line[line_number][word]++;
    }
}
bool KeywordsInFile::KeywordFound(const std::string &keyword)
{
    return keywords[keyword] > 0;
}
int KeywordsInFile::KeywordInLine(const std::string &keyword, const int &line_number)
{
    return keywords_in_line[line_number][keyword];
}
int KeywordsInFile::TotalOccurrences(const std::string &keyword)
{
    return keywords[keyword];
}

std::ostream& operator<<(std::ostream& os, const KeywordsInFile &kif)
{
    for(const auto &it : kif.keywords)
    {
        os<<"Keyword: "<<it.first<<" Occurrences: "<<it.second<<std::endl;
    }
    return os;
}