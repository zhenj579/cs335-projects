#include "Field.h"

Field::Field(const std::vector<std::vector<int>> &v) {
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
}

Field::Field(std::vector<std::vector<int>> && rhs) {
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

int Field::Weight(int x1, int y1, int x2, int y2) {
    if(x1 < 0 || y1 < 0  || x2 < 0 || y2 < 0 || x1 >= dp[0].size() || x2 >= dp[0].size() || y1 >= dp.size() || y2 >= dp.size()) throw std::out_of_range("out of bounds");
    int startx = 0;
    int endx = 0;
    int starty = 0;
    int endy = 0;
    startx = std::min(x1,x2); // min(1,4) = 1
    endx = std::max(x1,x2); // max(1,4) =  4
    starty = std::min(y1,y2); // min(2,0) = 0
    endy = std::max(y1,y2); // max(2,0) = 2
    //y in dp is x
    //x in dp is y
    if(startx == endx && starty == endy) return dp[starty][startx]-dp[starty-1][startx] - dp[starty][startx-1] + dp[starty-1][startx-1]; // same point
    if(starty == endy && endy > 0) return dp[endy][endx] - dp[endy-1][endx]; // horizontal line
    if(endy == 0 && starty == endy) return dp[endy][endx]-dp[endy][startx-1 >= 0 ? startx-1 : 0]; // horizontal line but at the top
    if(startx == endx && endx > 0) return dp[endy][endx] - dp[endy][endx-1]; // vertical line
    if(endx == 0 && startx == endx) return dp[endy][endx];
    return dp[endy][endx] - dp[starty+1][startx-1] - dp[starty-1][startx+1] + dp[starty-1][startx-1];

}

int Field::PathCost() {
    if(dp.empty()) return 0;
    else if(dp.size() == 1) return dp[0][dp[0].size()-1];
    else if(dp[0].size() == 1) return dp[dp.size()-1][0];
    int cost = dp[0][0];
    int i = 0;
    int j = 0;
    int curr,right,down;
    while(i != dp.size()-1 || j != dp[0].size()-1)
    {
        curr = dp[i][j];
        if(i == 0 && j == 0)
        {
            right = dp[i][j+1]-curr;
            down = dp[i+1][j]-curr;
            if(right < down)
            {
                cost+=right;
                j++;
            }
            else
            {
                cost+=down;
                i++;
            }
        }
        else if(i == 0 && j < dp[0].size()-1)
        {
            right = dp[i][j+1]-curr;
            down = dp[i+1][j]-curr-dp[i+1][j-1]+dp[i][j-1];
            if(right < down)
            {
                cost+=right;
                j++;
            }
            else
            {
                cost+=down;
                i++;
            }
        }
        else if(i == dp.size()-1)
        {
            right = dp[i][j+1]-curr-dp[i-1][j+1]+dp[i-1][j];
            cost+=right;
            j++;
        }
        else if(j == dp[0].size()-1)
        {
            down = dp[i+1][j]-dp[i+1][j-1]-curr+dp[i][j-1];
            cost+=down;
            i++;
        }
        else
        {
            right = dp[i][j+1]-curr-dp[i-1][j+1]+dp[i-1][j];
            down = dp[i+1][j]-curr-dp[i+1][j-1]+dp[i][j-1];
            if(right < down)
            {
                cost+=right;
                j++;
            }
            else
            {
                cost+=down;
                i++;
            }
        }
    }
    return cost;
}

std::ostream &operator<<(std::ostream &os, const Field &f) {
    for(const auto &v : f.dp)
    {
        for(const auto &e : v)
        {
            os<<e<<" ";
        }
        os<<"\n";
    }
    return os;

}


