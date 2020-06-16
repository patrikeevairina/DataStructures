#include "DoubleLinkedList.h"
#include <cassert>

DoubleLinkedList::Node::Node(const ValueType& value, Node *next, Node *previous)
    :value(value), previous(previous), next(next) {};

DoubleLinkedList::Node::~Node()
{}

void DoubleLinkedList::Node::insertNext(const ValueType &value)
{
    if (this->next != nullptr)
        Node *newNode = new Node(value, this->next, this);
    else
    {
        Node *newNode = new Node(value, nullptr, this);
    }
}

void DoubleLinkedList::Node::removeNext()
{
    Node* removeNode = this->next;
    if (this->next == nullptr)
        return;
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
    newNext->previous = this;
}

DoubleLinkedList::DoubleLinkedList()
    :_tail(nullptr), _head(nullptr), _size(0)
{}

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& copyList)
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

DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList &copyList)
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

DoubleLinkedList::~DoubleLinkedList()
{
    forceNodeDelete(_head);
}

ValueType& DoubleLinkedList::operator[](const size_t pos)
{
    return getNode(pos)->value;
}

const ValueType& DoubleLinkedList::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

DoubleLinkedList::Node* DoubleLinkedList::getNode(const size_t pos) const //working
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

void DoubleLinkedList::insert(const size_t pos, const ValueType &value)
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

void DoubleLinkedList::pushFront(const ValueType &value)
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


void DoubleLinkedList::pushBack(const ValueType &value)
{
    Node *newTail = new Node(value, nullptr, _tail);
    if (_tail != nullptr)
        _tail->next = newTail;
    else if (_head == nullptr)
        _head = newTail;
    _tail = newTail;
    _size++;
}

void DoubleLinkedList::insertAfterNode(Node *node, const ValueType &value)
{
    node->insertNext(value);
    _size++;
}

void DoubleLinkedList::removeBack()
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

void DoubleLinkedList::removeFront()
{
    if (_head == nullptr)
        throw std::invalid_argument("list is empty");
    Node* newHead = _head;
    _head = _head->next;
    delete newHead;
    --_size;
}

void DoubleLinkedList::remove(const size_t pos)
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

void DoubleLinkedList::removeNextNode(Node *node)
{
    if (node->next == nullptr)
        return;
    node->removeNext();
    _size--;
    return;
}

long long int DoubleLinkedList::findIndex(const ValueType& value) const
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

DoubleLinkedList::Node* DoubleLinkedList::findNode(const ValueType &value) const
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

void DoubleLinkedList::reverse()
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

DoubleLinkedList DoubleLinkedList::reverse() const
{
    DoubleLinkedList l = *this;
    return l.getReverseList();
}

DoubleLinkedList DoubleLinkedList::getReverseList()
{
    DoubleLinkedList *l = this;
    l->reverse();
    return *l;
}

size_t DoubleLinkedList::size() const
{
    return _size;
}

void DoubleLinkedList::forceNodeDelete(Node *node)
{
    if (node == nullptr)
        return;
    
    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}

