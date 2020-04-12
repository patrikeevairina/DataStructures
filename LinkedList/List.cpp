#include "List.h"
#include <iostream>
#include <cassert>

List::Node::Node(const ValueType& value, Node *next, Node *previous)
{
    this->value = value;
    this->next = next;
    this->previous = previous;
}

List::Node::~Node()
{
    //
}

void List::Node::insertNext(const ValueType &value)//not sure
{
    Node *newNode = new Node(value, this->next, this);
    this->next = newNode;
    newNode->previous = this;

}

void List::Node::removeNext()
{
    if (this->next != nullptr)
    {
        Node *removeNode = this->next;
        Node *newNext = this->next->next;
        newNext->previous = this;
        delete[] removeNode;
        this->next = newNext;
    }
}

List::List()
    :_tail(nullptr), _head(nullptr), _size(0)
{

}

List::List(const List& copyList)
{
    this->_size = copyList._size;
    this->_head = new Node(copyList._head->value, nullptr, nullptr);
    if (_size > 1)
    {
        this->_tail = new Node(copyList._tail->value, nullptr, nullptr);
    }
    else
    {
        this->_tail = this->_head;
    }

    Node *currCopy = copyList._head;
    Node *curr = this->_head;
    while (currCopy->next != copyList._tail)
    {
        curr->next = new Node(currCopy->next->value, nullptr, curr);
        curr = curr->next;
        currCopy = currCopy->next;
    }
    curr->next = this->_tail;
}

List& List::operator=(const List &copyList)//DONT FORGET
{
    if (this == &copyList)
    {
        return *this;
    }
    List bufList(copyList);
    this->_size = bufList._size;
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

ValueType& List::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

List::Node* List::getNode(const size_t pos) const //working
{
    if (pos < 0)
    {
        assert(pos < 0);
    }
    else if (pos >= this->_size)
    {
        assert(pos >= this->_size);
    }

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

void List::insert(const size_t pos, const ValueType &value)
{
    if (pos < 0)
    {
        assert(pos < 0);
    }
    else if (pos > this->_size)
    {
        assert(pos > this->_size);
    }

    if (pos == 0)
    {
        pushFront(value);
    }
    else if (pos == _size)
    {
        pushBack(value);
    }
    else
    {
        Node *neigh1 = getNode(pos - 1);
        Node *neigh2 = getNode(pos);
        Node *newNode = new Node(value, neigh2, neigh1);
        neigh1->next = newNode;
        neigh2->previous = newNode;
        _size++;
    }

}

void List::pushFront(const ValueType &value)//working
{
    Node *newHead = new Node(value, _head, nullptr);
    if (_head != nullptr)
    {
        _head->previous = newHead;
    }
    _head = newHead;

    if (_tail == nullptr)
    {
        _tail = newHead;
    }
    _size++;
}

void List::pushBack(const ValueType &value)//working
{
    Node *newTail = new Node(value, nullptr, _tail);
    if (_tail != nullptr)
    {
        _tail->next = newTail;
    }
    _tail = newTail;

    if (_head == nullptr)
    {
        _head = newTail;
    }

    _size++;
}

void List::insertAfterNode(Node *node, const ValueType &value)
{
    node->insertNext(value);
}

void List::removeBack()
{
    if (_size == 1)
    {
        forceNodeDelete(_head);
        _size--;
        return;
    }
    if (_tail == nullptr)
        return;

    Node *nd = _tail;
    _tail = _tail->previous;
    if (_tail != nullptr)
    {
        _tail->next = nullptr;
    }
    if (nd == _head)
    {
        _head = nullptr;
    }
    delete[] nd;
    _size--;
}

void List::removeFront()
{
    if (_size == 1)
    {
        forceNodeDelete(_head);
        _size--;
        return;
    }
    if (_head == nullptr)
        return;

    Node *nd = _head;
    _head = _head->next;
    if (_head != nullptr)
        _head->previous = nullptr;
    if (nd == _tail)
    {
        _tail = nullptr;
    }
    delete[] nd;
    _size--;
}

void List::remove(const size_t pos)
{
    if (pos > size() - 1)
    {
        return;
    }

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
    return;
}

void List::removeNextNode(Node *node)
{
    return node->removeNext();
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
        Node* temp = current->next;
        current->next = current->previous;
        current->previous = temp;
        current = temp;
    }
    current = _tail;
    _tail = _head;
    _head = current;

}

List List::reverse1() const
{
    List *l = new List;
    *l = *this;
    l->reverse();

    return *l;
}

List List::getReverseList()
{
    List *l = new List;
    *l = *this;
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
