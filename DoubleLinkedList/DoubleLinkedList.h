#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
#define ValueType double

class DoubleLinkedList
{
    struct Node {
        Node(const ValueType& value, Node* next = nullptr, Node *previous = nullptr);
        ~Node();
        
        void insertNext(const ValueType& value);
        void removeNext();
        
        ValueType value;
        Node* previous;
        Node* next;
        
    };
    
public:
    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList& copyList);
    DoubleLinkedList& operator=(const DoubleLinkedList& copyList);
    ~DoubleLinkedList();
    
    ValueType& operator[](const size_t pos);
    const ValueType& operator[](const size_t pos) const;
    DoubleLinkedList::Node* getNode(const size_t pos) const;
    
    void insert(const size_t pos, const ValueType& value);
    void insertAfterNode(Node* node, const ValueType& value);
    void pushBack(const ValueType& value);
    void pushFront(const ValueType& value);
    
    void remove(const size_t pos);
    void removeNextNode(Node* node);
    void removeFront();
    void removeBack();
    
    long long int findIndex(const ValueType& value) const;
    Node* findNode(const ValueType& value) const;
    
    void reverse();		
    DoubleLinkedList reverse() const;	
    DoubleLinkedList getReverseList();	
    
    size_t size() const;
private:
    Node* _tail;
    Node*	_head;
    size_t	_size;
    
    void forceNodeDelete(Node* node);
};

#endif
