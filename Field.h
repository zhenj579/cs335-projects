#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <vector>

class Field {

private:
    void computePathCost(const std::vector<std::vector<int>> &);
    std::vector<std::vector<int>> dp;
    int cost;
public:
    Field(const std::vector<std::vector<int>> &);
    Field(std::vector<std::vector<int>> &&);
    int Weight(int x1, int y1, int x2, int y2) const;
    int PathCost() const;
};


#endif
