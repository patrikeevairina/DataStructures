#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <exception>
#include <cstdlib>
#define ValueType double

class LinkedList
{
    struct Node {
        Node(const ValueType& value, Node* next = nullptr);
        ~Node();
        
        void insertNext(const ValueType& value);
        void removeNext();
        
        ValueType value;
        Node* next;
    };
private:
    Node*	_head;
    size_t	_size;
    
    void forceNodeDelete(Node* node);
    
public:
    
    LinkedList();
    LinkedList(const LinkedList& copyList);
    LinkedList& operator=(const LinkedList& copyList);
    
    LinkedList(LinkedList&& moveList) noexcept;
    LinkedList& operator=(LinkedList&& moveList) noexcept;
    
    ~LinkedList();
    
    const ValueType& operator[](const size_t pos) const;
    ValueType& operator[](const size_t pos);
    LinkedList::Node* getNode(const size_t pos) const;
    LinkedList::Node* getNode(const size_t pos);
    
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
    LinkedList reverse() const;	
    LinkedList getReverseList();	
    
    size_t size() const;
};

#endif // LINKEDLIST_H
