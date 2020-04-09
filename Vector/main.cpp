#include <iostream>
#include "vector.h"
#include "vector.cpp"

using namespace std;

void printVector(MyVector &v)
{
    cout << "Begin" << endl;
    for (ValueType *i = v.begin(); i < v.end(); i++)
        cout << *i << ", ";
    cout << "End" << endl;
}

int main()
{

    MyVector v(4, 3); // 3 3 3 3
    printVector(v);
    v.pushBack(4); // 3 3 3 3 4
    printVector(v);
    v.pushBack(100); // 3 3 3 3 4 100
    printVector(v);
    v.popBack(); // 3 3 3 3 4
    printVector(v);
    v.insert(0, 0); // 0 3 3 3 3 4
    printVector(v);
    MyVector c(2, 1);
    v.insert(1, c); // 0 1 1 3 3 3 3 4
    printVector(v);
    v.erase(2); // 0 1 3 3 3 3 4
    printVector(v);
    v.erase(3, 2); // 0 1 3 3 4
    printVector(v);
    v.insert(2, 2); // 0 1 2 3 3 4
    printVector(v);
    v.resize(7, 5); // 0 1 2 3 3 4 5
    printVector(v);
    return 0;
}
