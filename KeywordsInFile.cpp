#include "KeywordsInFile.h"
KeywordsInFile::KeywordsInFile(const std::string &filename_with_keywords, const std::string &filename_with_text)
{
    std::ifstream file(filename_with_keywords);
    std::string word;
    char c;
    int line_number = 1;
    while(!file.eof())
    {
        c = file.get();
        if(!isalpha(c))
        {
            keywords.insert(std::make_pair(word, 0)); // insert all keywords to unordered_map
            word = "";
        }
        else
        {
            word+=c;
        }
    }
    file.close();
    file.open(filename_with_text);
    while(!file.eof())
    {

        c = file.get();
        if(c == '\n')
        {
            line_number++;
        }
        if(!isalpha(c))
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
            word="";
        }
        else
        {
            word+=c;
        }
    }
    file.close();
}
bool KeywordsInFile::KeywordFound(const std::string &keyword) const
{
    return keywords.find(keyword) != keywords.end();
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
    os<<"KEYWORDS AND OCCURRENCES:"<<std::endl;
    for(const auto &it : kif.keywords)
    {
        os<<"Keyword: "<<it.first<<" Occurrences: "<<it.second<<std::endl;
    }
    os<<"----------------------------------------------"<<std::endl;
    os<<"LINE NUMBERS WITH KEYWORDS AND OCCURRENCES:"<<std::endl;
    for(const auto &it : kif.keywords_in_line)
    {
        for(const auto &it1 : it.second)
        {
            os<<"Line Number: "<<it.first<<" Keyword: "<<it1.first<<" Occurrences: "<<it1.second<<std::endl;
        }
        os<<"----------------------------------------------"<<std::endl;
    }
    return os;
}