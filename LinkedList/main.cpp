#include <iostream>
#include "LinkedList.h"
//#include "LinkedList.cpp"

using namespace std;

void printList(const LinkedList &c)
{
    cout << "begin" << endl;
    for (size_t i = 0; i < c.size(); i++)
        cout << c[i] << " ";
    cout << " end!" << endl;
}

int main()
{
    LinkedList v;

    LinkedList c;
    for (size_t i = 0; i < 10; i++)
    {
        c.insert(i,i);
    }
    printList(c);

    for (size_t i = 0; i < 11; i++)
    {
        v.insert(i,10 - i);

    }
    printList(v);

    c = v;
    printList(c);
    return 0;
}
