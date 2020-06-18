#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
//#define ValueType double

template <typename ValueType>
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

template <typename ValueType>
DoubleLinkedList<ValueType>::Node::Node(const ValueType& value, Node *next, Node *previous)
    :value(value), previous(previous), next(next) {};

template <typename ValueType>
DoubleLinkedList<ValueType>::Node::~Node()
{}

template <typename ValueType>
void DoubleLinkedList<ValueType>::Node::insertNext(const ValueType &value)
{
    if (this->next != nullptr)
        Node *newNode = new Node(value, this->next, this);
    else
    {
        Node *newNode = new Node(value, nullptr, this);
    }
}

template <typename ValueType>
void DoubleLinkedList<ValueType>::Node::removeNext()
{
    Node* removeNode = this->next;
    if (this->next == nullptr)
        throw std::invalid_argument("invalid arg");
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
    newNext->previous = this;
}

template <typename ValueType>
DoubleLinkedList<ValueType>::DoubleLinkedList()
    :_tail(nullptr), _head(nullptr), _size(0)
{}

template <typename ValueType>
DoubleLinkedList<ValueType>::DoubleLinkedList(const DoubleLinkedList& copyList)
{
    _size = copyList._size;
    if (_size == 0) {
        _head = nullptr;
        _tail = nullptr;
        return;
    }
    _head = new Node(copyList._head->value);
    Node* currentNode = _head;
    Node* currentCopyNode = copyList._head;
    while (currentCopyNode->next)
    {
        currentCopyNode = currentCopyNode->next;
        currentNode->next = new Node(currentCopyNode->value, 0, currentNode);
        currentNode = currentNode->next;
    }
    _tail = currentNode;
}

template <typename ValueType>
DoubleLinkedList<ValueType>& DoubleLinkedList<ValueType>::operator=(const DoubleLinkedList &copyList)
{
    if (this == &copyList)
    {
        return *this;
    }
    DoubleLinkedList* bufList = new DoubleLinkedList(copyList);
    forceNodeDelete(_head);
    this->_size = bufList->_size;
    this->_head = bufList->_head;
    this->_tail = bufList->_tail;
    return *this;
}

template <typename ValueType>
DoubleLinkedList<ValueType>::~DoubleLinkedList()
{
    forceNodeDelete(_head);
}

template <typename ValueType>
ValueType& DoubleLinkedList<ValueType>::operator[](const size_t pos)
{
    return getNode(pos)->value;
}

template <typename ValueType>
const ValueType& DoubleLinkedList<ValueType>::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

template <typename ValueType>
typename DoubleLinkedList<ValueType>::Node* DoubleLinkedList<ValueType>::getNode(const size_t pos) const //working
{
    if (pos >= _size)
        throw std::out_of_range("out_of_range");
    Node *current;
    if (pos < _size / 2)
    {
        current = _head;
        for (size_t i = 0; i < pos; i++)
        {
            current = current->next;
        }
    }
    else
    {
        current = _tail;
        for (size_t k = _size - 1; k > pos; k--)
        {
            current = current->previous;
        }
    }
    return current;
}

template <typename ValueType>
void DoubleLinkedList<ValueType>::insert(const size_t pos, const ValueType &value)
{
    if (pos > _size)
        throw std::out_of_range("out_of_range");
    if (pos == 0)
    {
        pushFront(value);
        return;
    }
    else if (pos == _size)
    {
        pushBack(value);
        return;
    }
    else
    {
        Node *node = getNode(pos - 1);
        node->insertNext(value);
        _size++;
        return;
    }
}

template <typename ValueType>
void DoubleLinkedList<ValueType>::pushFront(const ValueType &value)
{
    if (_head == nullptr)
    {
        Node *newHead = new Node(value, 0, 0);
        _head = newHead;
        _tail = _head;
        _size++;
        return;
    }
    Node *newHead = new Node(value, _head, nullptr);
    _head = newHead;
    _size++;
}


template <typename ValueType>
void DoubleLinkedList<ValueType>::pushBack(const ValueType &value)
{
    Node *newTail = new Node(value, nullptr, _tail);
    if (_tail != nullptr)
        _tail->next = newTail;
    else if (_head == nullptr)
        _head = newTail;
    _tail = newTail;
    _size++;
}

template <typename ValueType>
void DoubleLinkedList<ValueType>::insertAfterNode(Node *node, const ValueType &value)
{
    node->insertNext(value);
    _size++;
}

template <typename ValueType>
void DoubleLinkedList<ValueType>::removeBack()
{
    if (_size == 0)
        throw std::out_of_range("out_of_range");
    if (_size == 1)
    {
        delete _head;
        _head = nullptr;
        _size--;
        return;
    }
    Node *newTail = _tail;
    newTail = newTail->previous;
    delete _tail;
    _tail = newTail;
    newTail->next = nullptr;
    _size--;
}

template <typename ValueType>
void DoubleLinkedList<ValueType>::removeFront()
{
    if (_head == nullptr)
        throw std::invalid_argument("list is empty");
    Node* newHead = _head;
    _head = _head->next;
    delete newHead;
    --_size;
}

template <typename ValueType>
void DoubleLinkedList<ValueType>::remove(const size_t pos)
{
    if (pos >= _size)
        throw std::out_of_range("out_of_range");
    if (pos == 0)
    {
        removeFront();
        return;
    }
    if (pos == _size - 1)
    {
        removeBack();
        return;
    }
    
    Node *nd = getNode(pos - 1);
    nd->removeNext();
    _size--;
}

template <typename ValueType>
void DoubleLinkedList<ValueType>::removeNextNode(Node *node)
{
    if (node->next == nullptr)
        return;
    node->removeNext();
    _size--;
    return;
}

template <typename ValueType>
long long int DoubleLinkedList<ValueType>::findIndex(const ValueType& value) const
{
    Node *current = _head;
    for (long long int i = 0; i < _size; i++)
    {
        if (current->value == value)
            return i;
        current = current->next;
    }
    return -1;
}

template <typename ValueType>
typename DoubleLinkedList<ValueType>::Node* DoubleLinkedList<ValueType>::findNode(const ValueType &value) const
{
    Node *current = _head;
    for (long long int i = 0; i < _size; i++)
    {
        if (current->value == value)
            return current;
        current = current->next;
    }
    return nullptr;
}

template <typename ValueType>
void DoubleLinkedList<ValueType>::reverse()
{
    if ((_size == 1)||(_size ==0))
        return;
    Node *current = _head;
    while (current != nullptr)
    {
        Node* temp = current->next;
        current->next = current->previous;
        current->previous = temp;
        current = temp;
    }
    current = _tail;
    _tail = _head;
    _head = current;
}

template <typename ValueType>
DoubleLinkedList<ValueType> DoubleLinkedList<ValueType>::reverse() const
{
    DoubleLinkedList l = *this;
    return l.getReverseList();
}

template <typename ValueType>
DoubleLinkedList<ValueType> DoubleLinkedList<ValueType>::getReverseList()
{
    DoubleLinkedList *l = this;
    l->reverse();
    return *l;
}

template <typename ValueType>
size_t DoubleLinkedList<ValueType>::size() const
{
    return _size;
}

template <typename ValueType>
void DoubleLinkedList<ValueType>::forceNodeDelete(Node *node)
{
    if (node == nullptr)
        return;
    
    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}



#endif
