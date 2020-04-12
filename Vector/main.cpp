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

    MyVector v;
    v.insert(0,0);
        printVector(v);
    v.pushBack(1);
        printVector(v);
    v.insert(2,2);
        printVector(v);
    MyVector c(2,3);
    v.insert(3,c);
//    cout << "num1: " << v.capacity() << " " << v.size() << endl;
    v.resize(10, 4);
//     cout << "num2: " << v.capacity() << " " << v.size() << endl;
    printVector(v);
    MyVector v1;
    v1 = v;
    printVector(v1);
    MyVector v2 = v;
    printVector(v2);
    return 0;
}
