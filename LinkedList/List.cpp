#include "List.h"
#include <iostream>
#include <cassert>

List::Node::Node(const ValueType& value, Node *next, Node *previous)
{
    this->value = value;
    this->previous = previous;
    this->next = next;
}

List::Node::~Node()
{

}

void List::Node::insertNext(const ValueType& value)
{
//    std::cout << "insertNext starts " << std::endl;
    Node *newNode = new Node(value, this->next, this);
    this->next = newNode;
//    std::cout << "insertNext ends " << std::endl;
}

void List::Node::removeNext()
{
    Node *removeNode = this->next;
    Node *newNext = removeNode->next;
    newNext->previous = this;
    delete removeNode;
    this->next = newNext;
}

List::List()
    :_tail(nullptr), _head(_tail), _size(0)
{

}

List::List(const List& copyList)
{
    this->_size = copyList._size;
    this->_head = new Node(copyList._head->value);
    Node *currCopy = copyList._head;
    Node *curr = this->_head;
    while (currCopy->next != nullptr)
    {
        curr->next = new Node(currCopy->next->value, nullptr, curr);
        curr = curr->next;
        currCopy = currCopy->next;
    }
    this->_tail = curr;
}

List& List::operator=(const List &copyList)//пока забила, оно не работает, в общем
{
    if (this == &copyList)
        return *this;
    List bufList(copyList);
    this->_size = bufList._size;
    this->_head = bufList._head;
    

    return *this;
}

List::~List()
{
    forceNodeDelete(_head);
}

ValueType& List::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

List::Node* List::getNode(const size_t pos) const
{
    if (pos < 0)
        assert(pos < 0);
    else if (pos >= this->_size)
        assert(pos >= this->_size);


    Node *bufNode = this->_head;
    for (size_t i = 0; i < pos; i++)
        bufNode = bufNode->next;

    return bufNode;
}

void List::insert(const size_t pos, const ValueType &value)
{
    if (pos < 0)
        assert(pos < 0);
    else if (pos > this->_size)
        assert(pos > _size);

    if (pos == 0)
        pushFront(value);
    else
    {
        Node* bufNode = this->_head;
//        std::cout << "head value - " << bufNode->value << std::endl;
        for (size_t i = 0; i < pos - 1; i++)
            bufNode = bufNode->next;
//        std::cout << "current value - " << bufNode->value << std::endl;
        bufNode -> insertNext(value);
//        std::cout << "bufNode->next->value - " << bufNode->next->value << std::endl;
//        std::cout << "value of tail - " << _tail->value << std::endl;
        if (pos == _size)
            _tail = _tail->next;
//        std::cout << "value of tail - " << _tail->value << std::endl;
        _size++;
    }
}

void List::pushFront(const ValueType &value)
{
//    std::cout << "okay" << std::endl;
    _head = new Node(value, _head, nullptr);
    if (_size == 0)
        _tail = _head;
    _size++;
//    std::cout << "size - " << _size << std::endl;
}

size_t List::size() const
{
    return _size;
}

void List::forceNodeDelete(Node *node)
{
    if (node == nullptr)
        return;
    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);

}
