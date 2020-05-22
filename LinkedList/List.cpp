#include "List.h"
#include <iostream>
#include <cassert>

List::Node::Node(const ValueType& value, Node *next, Node *previous)
{
    this->value = value;
    this->next = next;
    this->previous = previous;

    if (previous != nullptr)
        previous->next = this;

    if (next != nullptr)
        next->previous = this;

}

List::Node::~Node()
{
    //
}

void List::Node::insertNext(const ValueType &value)
{
    if (this->next != nullptr)
        Node *newNode = new Node(value, this->next, this);
    else
    {
        Node *newNode = new Node(value, nullptr, this);
    }

}

void List::Node::removeNext()
{
    Node* removeNode = this->next;
    if (this->next == nullptr)
        return;
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
    newNext->previous = this;
}

List::List()
    :_tail(nullptr), _head(nullptr), _size(0)
{

}

List::List(const List& copyList)
{
  
    this->_size = copyList._size;
    this->_head = new Node(copyList._head->value, nullptr, nullptr);
    if (_size < 2)
    {
        this->_tail = this->_head;
        return;
    }

    Node *currCopy = copyList._head;
    Node *curr = this->_head;
    while (currCopy->next != copyList._tail)
    {
        curr->next = new Node(currCopy->next->value, nullptr, curr);
        curr = curr->next;
        currCopy = currCopy->next;
    }
   
    _tail = new Node(currCopy->next->value, nullptr, curr);
   
    
}

List& List::operator=(const List &copyList)//DONT FORGET
{
    if (this == &copyList)
    {
        return *this;
    }
    List bufList(copyList);
    this->_size = bufList._size;
    if (_head != nullptr)
    {
       
        forceNodeDelete(_head);
        delete _head;
    }

    this->_head = new Node(bufList._head->value);
    Node *currCopy = bufList._head;
    Node *curr = this->_head;
    while (currCopy->next != nullptr)
    {
        curr->next = new Node(currCopy->next->value, nullptr, curr);
        curr = curr->next;
        currCopy = currCopy->next;
    }
    _tail = curr;

    return *this;

}

List::~List()
{
    forceNodeDelete(_head);
}

ValueType& List::operator[](const size_t pos)
{
    return getNode(pos)->value;
}

const ValueType& List::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

List::Node* List::getNode(const size_t pos) const //working
{
    try
    {
        if (pos >= _size)
            throw std::out_of_range("error");
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
    catch(std::out_of_range &e)
    {
        std::cout << "incorrect idx" << std::endl;
    }
}

void List::insert(const size_t pos, const ValueType &value)
{
    try
    {
        if (pos > _size)
            throw std::out_of_range("error");
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
    catch(std::out_of_range &e)
    {
        std::cout << "incorrect index" << std::endl;
    }
}

void List::pushFront(const ValueType &value)//вроде заработало
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

void List::pushBack(const ValueType &value)//working
{
    if (_head == nullptr)
    {
       
        pushFront(value);
        return;
    }
   
    Node *newTail = new Node(value, nullptr, _tail);
    _tail = newTail;
    _size++;
}

void List::insertAfterNode(Node *node, const ValueType &value)
{
    node->insertNext(value);
    _size++;
}

void List::removeBack()//работает на 1 элементе, на нескольких вроде тоже
{
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

void List::removeFront()
{
    try
    {
        if (_size == 0)
            throw std::out_of_range("error");
        if (_size == 1)
        {
            removeBack();
            return;
        }

        Node *newHead = _head;
        newHead = newHead->next;
        delete _head;
        _head = newHead;
        _head->previous = nullptr;
        _size--;
    }
    catch(std::out_of_range &e)
    {
        std::cout << "List was empty" << std::endl;
    }
}

void List::remove(const size_t pos)//вроде ничего не ломает
{
    try
    {
        if (pos >= _size)
            throw std::out_of_range("error");
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
    catch(std::out_of_range &e)
    {
        std::cout << "incorrect index" << std::endl;
    }
}

void List::removeNextNode(Node *node)
{
    if (node->next == nullptr)
        return;
    node->removeNext();
    _size--;
    return;
}

long long int List::findIndex(const ValueType& value) const
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

List::Node* List::findNode(const ValueType &value) const
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

void List::reverse()
{
    if (_size == 1)
        return;

    Node *current = _head;
    while (current != nullptr)
    {
//        std::cout << current->value << std::endl;
        Node* temp = current->next;
        current->next = current->previous;
        current->previous = temp;
        current = temp;
    }
    current = _tail;
    _tail = _head;
    _head = current;

}

List List::reverse() const
{
    List l = *this;
    return l.getReverseList();
}

List List::getReverseList()
{
    List *l = this;
    l->reverse();
    return *l;
}

size_t List::size() const
{
    return _size;
}

void List::forceNodeDelete(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}
