#include "Field.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main() {
    vector<vector<int>> v1 = { {1},
                               {1},
                               {1}};
    Field field(v1);
    assert(field.PathCost() == 3);
    assert(field.Weight(0,0,0,0) == 1);
    assert(field.Weight(0,1,0,0) == 2);
    assert(field.Weight(0,2,0,0) == 3);
    assert(field.Weight(0,0,0,2) == 3);
//    field.Weight(-1,-1,-1,-1); oob
//    field.Weight(1,0,1,0); oob
//    field.Weight(0,2,0,3); oob
    vector<vector<int>> v2 = { {1,1,1} };
    Field field1(v2);
    assert(field1.PathCost() == 3);
    assert(field1.Weight(0,0,0,0) == 1);
    assert(field1.Weight(1,0,1,0) == 1);
    assert(field1.Weight(2,0,2,0) == 1);
    assert(field1.Weight(0,0,1,0) == 2);
    assert(field1.Weight(2,0,0,0) == 3);
    assert(field1.Weight(2,0,1,0) == 2);

    vector<vector<int>> v3 = { {1} };
    Field field2(v3);
    assert(field2.PathCost()==1);
    assert(field2.Weight(0,0,0,0) == 1);
//    field2.Weight(1,0,0,1); oob

    vector<vector<int>> v4 = { {1,3},
                               {1,3},
                               {1,1} };
    Field field3(v4);
    cout<<field3.PathCost();
    assert(field3.PathCost()==4);
    assert(field3.Weight(0,0,0,0) == 1);
    assert(field3.Weight(0,0,1,2) == 9);
    assert(field3.Weight(1,2,0,0) == 9);
    assert(field3.Weight(1,0,0,1) == 6);
    return 0;
}
