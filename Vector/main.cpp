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

    MyVector c(5,0);
    MyVector k ;
    k = c;
    MyVector p(2,1);

    k.erase(1,4);

    k.insert(1,p);
    k.pushBack(2);
    k.erase(2);
    k.insert(k.size(), 3);
    k.resize(15, 4);
    cout << k.capacity() << " " << k.size() << endl;
    k.resize(5);
    cout << k.capacity() << " " << k.size() << endl;
    c = k.sortedSquares(k);
    printVector(c);
    return 0;
}
