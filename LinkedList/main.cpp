#include <iostream>
#include "LinkedList.h"
//#include "LinkedList.cpp"

using namespace std;

void printList(LinkedList &c)
{
    cout << "begin" << endl;
    for (size_t i = 0; i < c.size(); i++)
        cout << c[i] << endl;
    cout << " end!" << endl;
}

int main()
{
    LinkedList c;
    c.insert(0,1);
    c.insert(1,2);
    c.insert(2,3);
    c.insert(3,4);
    c.insert(4,5);

    LinkedList c1 = c;

    printList(c1);

    cout << "ok ";
    return 0;
}
