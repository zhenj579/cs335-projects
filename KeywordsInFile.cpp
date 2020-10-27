#include "KeywordsInFile.h"
KeywordsInFile::KeywordsInFile(const std::string &filename_with_keywords, const std::string &filename_with_text)
{
    std::ifstream file(filename_with_keywords);
    if(file.fail())
    {
        std::cout<<"failed to open file"<<std::endl;
        return;
    }
    std::string word;
    char c;
    int line_number = 1;
    while(file.good())
    {
        c = file.get();
        if(!isalpha(c) && !word.empty())
        {
            keywords.insert(std::make_pair(word, 0)); // insert all keywords to unordered_map
            word.clear();
        }
        if(isalpha(c)) word+=c;
    }
    file.close();
    file.open(filename_with_text);
    if(file.fail())
    {
        std::cout<<"failed to open file"<<std::endl;
        return;
    }
    while(file.good())
    {
        c = file.get();
        if(!isalpha(c) && !word.empty())
        {
            bool foundKeyword = keywords.find(word) != keywords.end();
            if(foundKeyword)
            {
                bool line_number_exists = keywords_in_line.find(line_number) != keywords_in_line.end();
                bool keyword_exists_in_line_number = line_number_exists && keywords_in_line.at(line_number).find(word) != keywords_in_line.at(line_number).end();
                keywords.at(word)++;
                //also keep track of the line number and keyword occurrences with another unordered_map
                if(!line_number_exists)
                {
                    std::unordered_map<std::string, int> entry; // create a new value for line_number unordered_map, this will keep track of the keyword and occurrences
                    entry.insert(std::make_pair(word, 1));
                    keywords_in_line.insert(std::make_pair(line_number, entry));
                }
                else if(!keyword_exists_in_line_number) // if line_number exists but the keyword was first encountered
                {
                    keywords_in_line.at(line_number).insert(std::make_pair(word, 1));
                }
                else
                {
                    keywords_in_line.at(line_number).at(word)++; // if line_number exists and word exists, just increment the existing number
                }
            }
            word.clear();
        }
        if(isalpha(c)) word+=c;
        if(c == '\n')
        {
            line_number++;
        }
    }
    file.close();
}
bool KeywordsInFile::KeywordFound(const std::string &keyword) const
{
    bool keyword_exists = keywords.find(keyword) != keywords.end();

    return keyword_exists && keywords.at(keyword) > 0;
}
int KeywordsInFile::KeywordInLine(const std::string &keyword, const int &line_number) const
{
    bool line_number_exists = keywords_in_line.find(line_number) != keywords_in_line.end();
    bool keyword_exists_in_line_number = line_number_exists && keywords_in_line.at(line_number).find(keyword) != keywords_in_line.at(line_number).end();
    if(keyword_exists_in_line_number)
    {
        return keywords_in_line.at(line_number).at(keyword);
    }
    else
    {
        return 0;
    }
}
int KeywordsInFile::TotalOccurrences(const std::string &keyword) const
{
    bool keyword_exists = keywords.find(keyword) != keywords.end();
    if(keyword_exists)
    {
        return keywords.at(keyword);
    }
    else
    {
        return 0;
    }
}

std::ostream& operator<<(std::ostream& os, const KeywordsInFile &kif)
{
    for(const auto &it : kif.keywords)
    {
        os<<"Keyword: "<<it.first<<" Occurrences: "<<it.second<<std::endl;
    }
    return os;
}