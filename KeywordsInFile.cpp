#include "KeywordsInFile.h"
KeywordsInFile::KeywordsInFile(const std::string &filename_with_keywords, const std::string &filename_with_text)
{
    std::ifstream file(filename_with_keywords);
    std::string word;
    int line_number = 1;
    while(file>>word)
    {
        keywords.insert(std::make_pair(word, 0)); // insert all keywords to unordered_map
    }
    file.close();
    file.open(filename_with_text);
    while(file>>word)
    {
        if(file.peek() == '\n') // if reached a new line, we are now on the next line
        {
            line_number++;
            continue;
        }
        else if(keywords.find(word) != keywords.end())
        {
            keywords.at(word)++; // if word is a keyword, increment occurrences
            //also keep track of the line number and keyword occurrences with another unordered_map
            if(keywords_in_line.find(line_number) == keywords_in_line.end()) // if line number does not exist
            {
                std::unordered_map<std::string, int> umap; // create a new value for line_number unordered_map, this will keep track of the keyword and occurrences
                umap.insert(std::make_pair(word, 1)); // insert the new found keyword with occurrence 1
                keywords_in_line.insert(std::make_pair(line_number, umap)); //insert the map associated with the line_number
            }
            else if(keywords_in_line.at(line_number).find(word) == keywords_in_line.at(line_number).end()) // if line_number exists but the keyword was first encountered
            {
                keywords_in_line.at(line_number).insert(std::make_pair(word, 1)); //go to the line_number's unordered_map and create a new entry
            }
            else
            {
                keywords_in_line.at(line_number).at(word)++; // if line_number exists and word exists, just increment the existing number
            }
        }
    }
}
bool KeywordsInFile::KeywordFound(const std::string &keyword) const
{
    return keywords.find(keyword) != keywords.end();
}
int KeywordsInFile::KeywordInLine(const std::string &keyword, const int &line_number) const
{
    return keywords_in_line.find(line_number) != keywords_in_line.end() && // the line number exists
           keywords_in_line.at(line_number).find(keyword) != keywords_in_line.at(line_number).end() ? // keyword exists
           keywords_in_line.at(line_number).at(keyword) : 0; // if both preconditions are true then return the keyword occurrences else return 0.
}
int KeywordsInFile::TotalOccurrences(const std::string &keyword) const
{
    return keywords.find(keyword) != keywords.end() ? keywords.at(keyword) : 0; // if keyword exists return occurrences else return 0
}

std::ostream& operator<<(std::ostream& os, const KeywordsInFile &kif)
{
    os<<"KEYWORDS AND OCCURRENCES:----------------------------------------------"<<std::endl;
    for(const auto &it : kif.keywords)
    {
        os<<"Keyword: "<<it.first<<" Occurrences: "<<it.second<<std::endl;
    }
    os<<"----------------------------------------------"<<std::endl;
    os<<"LINE NUMBERS WITH KEYWORDS AND OCCURRENCES:----------------------------------------------"<<std::endl;
    for(const auto &it : kif.keywords_in_line)
    {
        os<<"Line Number: "<<it.first<<std::endl;
        for(const auto &it1 : it.second)
        {
            os<<" Keyword: "<<it1.first<<" Occurrences: "<<it1.second<<std::endl;
        }
    }

    return os;
}