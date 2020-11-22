#include "Field.h"

void Field::computePathCost(const std::vector<std::vector<int>> &v)
{
    std::vector<std::vector<int>> dpPathCost(v.size(), std::vector<int>(v[0].size()));
    if(v.empty() || v[0].empty()) cost = 0;
    else
    {
        dpPathCost[0][0] = v[0][0];
        for(int i = 1; i < v.size(); i++)
        {
            dpPathCost[i][0] = dpPathCost[i-1][0] + v[i][0];
        }
        for(int i = 1; i < v[0].size(); i++)
        {
            dpPathCost[0][i] = dpPathCost[0][i-1] + v[0][i];
        }
        for(int i = 1; i < v.size(); i++)
        {
            for(int j = 1; j < v[i].size(); j++)
            {
                dpPathCost[i][j] = std::min(dpPathCost[i-1][j], dpPathCost[i][j-1]) + v[i][j];
            }
        }
        cost = dpPathCost[dpPathCost.size()-1][dpPathCost[0].size()-1];
    }
}

Field::Field(const std::vector<std::vector<int>> &v)
{
    if(v.empty()) return;
    dp = std::vector<std::vector<int>>(v.size(),std::vector<int>(v[0].size()));
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j < v[i].size(); j++)
        {
            dp[i][j]+=v[i][j];
            if(i == 0 && j >= 1) dp[i][j]+=dp[i][j-1];
            else if(i >= 1 && j == 0) dp[i][j]+=dp[i-1][j];
            else if(i > 0 && j > 0) dp[i][j]+=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
        }
    }
    computePathCost(v);
}

Field::Field(std::vector<std::vector<int>> && rhs)
{
    std::vector<std::vector<int>> dpPathCost(rhs.size(), std::vector<int>(rhs[0].size()));
    computePathCost(rhs);
    dp = std::move(rhs);
    for(int i = 0; i < dp.size(); i++)
    {
        for(int j = 0; j < dp[i].size(); j++)
        {
            if(i == 0 && j >= 1) dp[i][j]+=dp[i][j-1];
            else if(i >= 1 && j == 0) dp[i][j]+=dp[i-1][j];
            else if(i > 0 && j > 0) dp[i][j]+=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
        }
    }

}

int Field::Weight(int x1, int y1, int x2, int y2) const
{
    bool outOfBounds = x1 < 0 || y1 < 0  || x2 < 0 || y2 < 0 || x1 >= dp[0].size() || x2 >= dp[0].size() || y1 >= dp.size() || y2 >= dp.size();
    if(outOfBounds) throw std::out_of_range("out of bounds");
    int startx = std::min(x1,x2);
    int endx = std::max(x1,x2);
    int starty = std::min(y1,y2);
    int endy = std::max(y1,y2);
    int curr = dp[endy][endx];
    if(startx > 0) curr -= dp[endy][startx-1];
    if(starty > 0) curr -= dp[starty-1][endx];
    if(startx > 0 && starty > 0) curr+=dp[starty-1][startx-1];
    return curr;
}

int Field::PathCost() const
{
    return cost;
}


