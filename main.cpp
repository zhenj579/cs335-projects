#include "Field.h"
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
    assert(field.Weight(0,0,0,0) == 1);
    assert(field.Weight(0,1,0,1) == 1);
    assert(field.Weight(0,2,0,2) == 1);
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
    assert(field1.Weight(0,0,0,0) == 1);
    assert(field1.Weight(1,0,1,0) == 1);
    assert(field1.Weight(2,0,2,0) == 1);
    assert(field1.Weight(1,0,2,0)==2);
    assert(field1.Weight(2,0,1,0)==2);


    vector<vector<int>> v3 = { {1} };
    Field field2(v3);
    assert(field2.PathCost()==1);
    assert(field2.Weight(0,0,0,0) == 1);
//    field2.Weight(1,0,0,1); oob

    vector<vector<int>> v4 = { {1,2},
                               {1,2},
                               {1,2} };
    Field field3(v4);
    assert(field3.PathCost()==5);
    assert(field3.Weight(0,0,0,0) == 1);
    assert(field3.Weight(0,0,1,2) == 9);
    assert(field3.Weight(1,2,0,0) == 9);
    assert(field3.Weight(1,0,0,1) == 6);
    assert(field3.Weight(0,0,0,0)==1);
    assert(field3.Weight(1,0,1,0)==2);
    assert(field3.Weight(0,1,0,1)==1);
    assert(field3.Weight(1,1,1,1)==2);
    assert(field3.Weight(0,2,0,2)==1);
    assert(field3.Weight(1,2,1,2)==2);

    vector<vector<int>> v5 = { {1,2,3},
                               {1,2,3} };
    Field field4(v5);
    assert(field4.Weight(0,0,0,0) == 1);
    assert(field4.Weight(1,0,1,0) == 2);
    assert(field4.Weight(2,0,2,0) == 3);
    assert(field4.Weight(0,1,0,1) == 1);
    assert(field4.Weight(1,1,1,1) == 2);
    assert(field4.Weight(2,1,2,1) == 3);
    assert(field4.Weight(0,1,1,1) == 3);
    assert(field4.Weight(1,1,2,1) == 5);
    assert(field4.PathCost()==7);

    assert(field4.Weight(0,0,0,1) == 2);
    assert(field4.Weight(1,0,1,1) == 4);
    assert(field4.Weight(2,0,2,1) == 6);
    assert(field4.Weight(0,0,1,0) == 3);
    assert(field4.Weight(1,0,0,0) == 3);
    assert(field4.Weight(1,0,2,0) == 5);
    assert(field4.Weight(2,0,1,0) == 5);
    assert(field4.Weight(0,1,1,1) == 3);
    assert(field4.Weight(1,1,0,1) == 3);
    assert(field4.Weight(0,0,0,0) == 1);
    assert(field4.Weight(1,0,1,0) == 2);
    assert(field4.Weight(2,0,2,0) == 3);
    assert(field4.Weight(0,1,0,1) == 1);
    assert(field4.Weight(1,1,1,1) == 2);
    assert(field4.Weight(2,1,2,1) == 3);
    assert(field4.Weight(0,0,2,1) == 12);
    assert(field4.Weight(2,1,0,0) == 12);
    assert(field4.Weight(1,1,0,0) == 6);
    assert(field4.Weight(1,1,2,0) == 10);
    assert(field4.Weight(2,0,1,1) == 10);
    assert(field4.Weight(0,0,1,1) == 6);
    assert(field4.Weight(2,0,2,1) == 6);
    assert(field4.Weight(0,0,2,0) == 6);
    assert(field4.Weight(2,0,0,0) == 6);
    assert(field4.Weight(0,1,2,1) == 6);
    assert(field4.Weight(1,0,2,0) == 5);
    assert(field4.Weight(2,0,1,0) == 5);
    assert(field4.Weight(0,0,0,1) == 2);
    assert(field4.Weight(0,1,0,0) == 2);
    assert(field4.Weight(1,0,1,1) == 4);
    assert(field4.Weight(1,1,1,0) == 4);
    assert(field4.Weight(2,0,2,1) == 6);
    assert(field4.Weight(2,1,2,0) == 6);
    vector<vector<int>> v6 = { {1,2,3},
                               {1,2,3},
                               {1,2,3} };
    Field field5(v6);
    assert(field5.PathCost() == 8);
    assert(field5.Weight(0,1,1,2)==6);
    assert(field5.Weight(1,2,0,1)==6);
    assert(field5.Weight(0,2,0,0)==3);
    assert(field5.Weight(1,0,1,2) == 6);
    assert(field5.Weight(2,2,1,1)==10);
    assert(field5.Weight(1,1,2,2)==10);
    assert(field5.Weight(0,0,0,0) == 1);
    assert(field5.Weight(1,0,1,0) == 2);
    assert(field5.Weight(2,0,2,0) == 3);
    assert(field5.Weight(0,1,0,1) == 1);
    assert(field5.Weight(1,1,1,1) == 2);
    assert(field5.Weight(2,1,2,1) == 3);
    assert(field5.Weight(0,2,0,2) == 1);
    assert(field5.Weight(1,2,1,2) == 2);
    assert(field5.Weight(2,2,2,2) == 3);
    assert(field5.Weight(0,0,1,1)==6);
    assert(field5.Weight(1,1,0,0)==6);
    assert(field5.Weight(2,0,1,1)==10);
    assert(field5.Weight(1,1,2,0)==10);
    assert(field5.Weight(0,0,1,2)==9);
    assert(field5.Weight(1,2,0,0)==9);
    assert(field5.Weight(2,0,1,2)==15);
    assert(field5.Weight(1,2,2,0)==15);
    assert(field5.Weight(0,0,1,2)==9);
    assert(field5.Weight(1,2,0,0)==9);
    assert(field5.Weight(0,0,2,2)==18);
    assert(field5.Weight(0,2,2,0)==18);
    assert(field5.Weight(0,0,2,0) == 6);
    assert(field5.Weight(0,1,2,1) == 6);
    assert(field5.Weight(0,2,2,2) == 6);

    vector<vector<int>> v7= {  {1,2},
                               {1,2}};
    Field field7(v7);
    assert(field7.PathCost() == 4);
    assert(field7.Weight(0,0,0,0) == 1);
    assert(field7.Weight(1,0,1,0) == 2);
    assert(field7.Weight(0,1,0,1) == 1);
    assert(field7.Weight(1,1,1,1) == 2);
    assert(field7.Weight(0,0,1,0) == 3);
    assert(field7.Weight(1,0,0,0) == 3);
    assert(field7.Weight(0,1,1,1) == 3);
    assert(field7.Weight(1,1,0,1) == 3);
    assert(field7.Weight(0,0,0,1) == 2);
    assert(field7.Weight(0,1,0,0) == 2);
    assert(field7.Weight(1,1,1,0) == 4);
    assert(field7.Weight(1,0,1,1) == 4);

    vector<vector<int>> v8 = { {1,2,3,4},
                               {1,2,3,4},
                               {1,2,3,4},
                               {1,2,3,4} };
    Field field8(v8);
    assert(field8.Weight(3,3,2,2)==14);
    assert(field8.PathCost() == 13);
    assert(field8.Weight(2,1,3,2)==14);
    assert(field8.Weight(1,2,2,3)==10);
    assert(field8.Weight(3,3,2,2)==14);
    assert(field8.Weight(1,0,3,1)==18);
    assert(field8.Weight(0,0,0,2) == 3);
    assert(field8.Weight(0,0,0,1) == 2);
    assert(field8.Weight(0,0,0,3) == 4);
    assert(field8.Weight(1,0,1,1) == 4);
    assert(field8.Weight(1,0,1,2) == 6);
    assert(field8.Weight(1,0,1,3) == 8);
    assert(field8.Weight(2,0,2,1) == 6);
    assert(field8.Weight(2,0,2,2) == 9);
    assert(field8.Weight(2,0,2,3) == 12);
    assert(field8.Weight(3,0,3,1) == 8);
    assert(field8.Weight(3,0,3,2) == 12);
    assert(field8.Weight(3,0,3,3) == 16);
    assert(field8.Weight(0,0,1,1) == 6);
    assert(field8.Weight(0,3,1,2) == 6);
    assert(field8.Weight(3,3,2,2)==14);
    assert(field8.Weight(1,1,2,2)==10);
    assert(field8.Weight(3,3,2,2)==14);
    assert(field8.Weight(0,1,1,2)==6);
    assert(field8.Weight(3,1,2,2) == 14);
    assert(field8.Weight(1,0,2,1) == 10);

    vector<vector<int>> v9 = { {1,2,3,4,5},
                               {1,2,3,4,5},
                               {1,2,3,4,5},
                               {1,2,3,4,5} };
    Field field9(v9);
    assert(field9.Weight(4,3,2,1)==36);
    assert(field9.Weight(4,3,1,1)==42);
    assert(field9.Weight(3,3,1,1)==27);
    assert(field9.Weight(1,1,3,2) == 18);
    assert(field9.Weight(1,1,2,3)==15);
    assert(field9.Weight(0,1,1,3)==9);
    assert(field9.Weight(3,1,4,3) ==27);
    assert(field9.Weight(0,0,4,1)==30);
    assert(field9.Weight(0,3,4,3)==15);
    assert(field9.Weight(0,2,4,3)==30);

    vector<vector<int>> v10 = {{1,2,1,1,1},
                               {4,1,1,1,1},
                               {5,2,3,10,5},
                               {4,2,3,1,1} };
    Field field10(v10);
    assert(field10.PathCost() == 13);

    vector<vector<int>> v11 = { { 1,2,3,4,5,6},
                                { 1,2,3,4,5,6},
                                { 1,2,3,4,5,6},
                                { 1,2,3,4,5,6},
                                { 1,2,3,4,5,6}};
    Field field11(v11);
    assert(field11.PathCost() == 25);
    assert(field11.Weight(1,2,4,0) == 42);

    vector<vector<int>> v12 = { { 1,2,3,4,5,6},
                                { 1,2,3,4,5,6},
                                { 1,2,3,4,5,6},
                                { 1,2,3,4,5,6},
                                { 1,2,3,4,5,6}};
    Field field12(std::move(v12));
    assert(field12.PathCost() == 25);
    assert(field12.Weight(1,2,4,0) == 42);
    return 0;
}
