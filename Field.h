#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <vector>

class Field {

private:
    std::vector<std::vector<int>> dp;
public:
    Field(const std::vector<std::vector<int>> &);
    Field(std::vector<std::vector<int>> &&);
    int Weight(int x1, int y1, int x2, int y2);
    int PathCost();

    friend std::ostream& operator<<(std::ostream& os, const Field &f);
};


#endif
