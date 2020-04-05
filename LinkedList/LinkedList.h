#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <cstdlib>

template <typename T>
class LinkedList
{
    struct Node
    {
        Node(const T& value, Node *next = nullptr);
        ~Node();

        void insertNext(const T& value);
        void removeNext();

        T value;
        Node *next;
    };

    public:

        LinkedList();
        LinkedList(const LinkedList& copyList);
        LinkedList& operator=(const LinkedList& copyList);

        LinkedList(LinkedList&& moveList) noexcept;
        LinkedList& operator=(LinkedList&& moveList) noexcept;

        ~LinkedList();

        T& operator[](const size_t pos) const;
        LinkedList::Node *getNode(const size_t pos) const;

        void insert(const size_t pos, const T& value);//insert the element by idx
        static void insertAfterNode(Node *node, const T& value);
        void pushBack(const T& value);
        void pushFront(const T& value);

        void remove(const size_t pos); //работает 
        void removeNextNode(Node *node); //вроде работает
        void removeFront(); //работает, но вынуждает реверс падать (не реверс падает) 
        void removeBack(); //работать-то работает, но реверс все еще падает (оказалось, что просто падает:( )

        size_t findIndex(const T& value) const;
        Node *findNode(const T& value) const;

        void reverse();
        LinkedList reverse() const;
//		LinkedList getReversedList() const;

        size_t size() const;

    private:
        Node *_head;
        size_t _size;

        void forceNodeDelete(Node *node);
};

#endif // LINKEDLIST_H
