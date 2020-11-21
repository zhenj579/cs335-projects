#include "Field.h"

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
    if(dp.empty()) return 0;
    bool outOfBounds = x1 < 0 || y1 < 0  || x2 < 0 || y2 < 0 || x1 >= dp[0].size() || x2 >= dp[0].size() || y1 >= dp.size() || y2 >= dp.size();
    if(outOfBounds) throw std::out_of_range("out of bounds");
    int startx = 0;
    int endx = 0;
    int starty = 0;
    int endy = 0;

    startx = std::min(x1,x2);
    endx = std::max(x1,x2);
    starty = std::min(y1,y2);
    endy = std::max(y1,y2);
    //y in dp is x
    //x in dp is y
    bool samePointAtTop = startx == endx && starty == 0 && endy == 0; // same point at the outer most part of the matrix
    bool samePoint = startx == endx && starty == endy; // same point not at border of matrix
    bool horizontalLine = starty == endy && endy > 0; //points form a horizontal line
    bool horizontalLineAtTop = endy == 0 && starty == endy;
    bool verticalLine = startx == endx && endx > 0;
    bool verticalLineAtLeft = endx == 0 && startx == 0;
    bool topLeftSquare = startx == 0 && starty == 0;
    bool leftSquare = startx == 0 && endx >= 1;
    bool topRightSquare = endx == dp[0].size()-1 && starty == 0;
    bool bottomRightSquare = endy == dp.size()-1 && endx == dp[0].size()-1;
    bool middleSquare = startx >= 1 && endx < dp[0].size()-1;
    if(samePointAtTop)
    {
        if(startx > 0)
        {
            return dp[endy][endx] - dp[endy][endx-1];
        }
        return dp[endy][endx];
    }
    if(samePoint)
    {
        if(endx == 0)
        {
            return dp[starty][startx]-dp[starty-1][startx];
        }
        return dp[starty][startx]-dp[starty-1][startx] - dp[starty][startx-1] + dp[starty-1][startx-1]; // same point
    }
    if(horizontalLine)
    {
        if(startx == 0)
        {
            return dp[endy][endx]-dp[endy-1][endx];
        }
        return dp[endy][endx] - dp[endy-1][endx] - dp[starty][startx-1] + dp[starty-1][startx-1]; // horizontal line
    }
    if(horizontalLineAtTop)
    {
        if(startx == 0)
        {
            return dp[endy][endx];
        }
        return dp[endy][endx]-dp[endy][startx-1]; // horizontal line but at the top
    }
    if(verticalLineAtLeft || topLeftSquare) return dp[endy][endx];
    if(verticalLine) return dp[endy][endx] - dp[endy][endx-1]; // vertical line
    if(topRightSquare) return dp[endy][endx]-dp[endy][startx-1];
    if(bottomRightSquare || middleSquare)
    {
        if(startx == 0) return dp[endy][endx]-dp[starty-1][endx];
        else if(starty == 0) return dp[endy][endx] - dp[endy][startx-1];
        return dp[endy][endx] - dp[endy][startx-1] - dp[starty-1][endx] + dp[starty-1][startx-1];
    }
    if(leftSquare) return dp[endy][endx] - dp[starty-1][endx];
    return dp[endy][endx] - dp[starty+1][startx-1] - dp[starty-1][startx+1] + dp[starty-1][startx-1];

}

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

int Field::PathCost() const
{
    return cost;
}


