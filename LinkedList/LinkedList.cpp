#include "LinkedList.h"
/*

LinkedList::Node::Node(const ValueType& value, Node* next)
{
    this->value = value;
    this->next = next;
}

LinkedList::Node::~Node()
{}


void LinkedList::Node::insertNext(const ValueType& value)
{
    Node* newNode = new Node(value, this->next);
    this->next = newNode;
}

void LinkedList::Node::removeNext()
{
    Node* removeNode = this->next;
    if (this->next == nullptr)
        return;
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
}

LinkedList::LinkedList()
    : _head(nullptr), _size(0)
{}

LinkedList::LinkedList(const LinkedList& copyList)//norm
{
    this->_size = copyList._size;
    this->_head = new Node(copyList._head->value);
    Node *currCopy = copyList._head;
    Node *curr = this->_head;
    
    while (currCopy->next != nullptr)
    {
        curr->next = new Node(currCopy->next->value);
        curr = curr->next;
        currCopy = currCopy->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
    if (this == &copyList) {
        return *this;
    }
    LinkedList bufList(copyList);
    this->_size = bufList._size;
    if (this->_head != nullptr)
    {
        forceNodeDelete(_head);
        //delete _head;
    }
    this->_head = new Node(bufList._head->value);
    Node *curr = _head;
    Node *currCopy = bufList._head;
    
    while (currCopy->next != nullptr)
    {
        curr->next = new Node(currCopy->next->value);
        curr = curr->next;
        currCopy = currCopy->next;
    }
    return *this;
}

LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->_head = moveList._head;
    
    moveList._size = 0;
    moveList._head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
    if (this == &moveList) {
        return *this;
    }
    forceNodeDelete(_head);
    this->_size = moveList._size;
    this->_head = moveList._head;
    
    moveList._size = 0;
    moveList._head = nullptr;
    
    return *this;
}

LinkedList::~LinkedList()
{
    forceNodeDelete(_head);
}

const ValueType& LinkedList::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

ValueType& LinkedList::operator[](const size_t pos)
{
    return getNode(pos)->value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
{
    if (pos >= _size)
        throw std::out_of_range("out_of_range");
    Node* bufNode = this->_head;
    for (size_t i = 0; i < pos; ++i)
    {
        bufNode = bufNode->next;
    }
    return bufNode;
}

LinkedList::Node* LinkedList::getNode(const size_t pos)
{
    
    if (pos >= _size)
        throw std::out_of_range("out_of_range");
    Node* bufNode = this->_head;
    for (size_t i = 0; i < pos; ++i)
    {
        bufNode = bufNode->next;
    }
    return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value)
{
    if (pos > _size)
        throw std::out_of_range("out_of_range");
    if (pos == 0)
    {
        pushFront(value);
    }
    else
    {
        Node* bufNode = this->_head;
        for (size_t i = 0; i < pos-1; ++i)
        {
            bufNode = bufNode->next;
        }
        bufNode->insertNext(value);
        ++_size;
    }
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
    node->insertNext(value);
    _size++;
}

void LinkedList::pushBack(const ValueType& value)
{
    if (_size == 0) {
        pushFront(value);
        return;
    }
    insert(_size, value);
}

void LinkedList::pushFront(const ValueType& value)
{
    _head = new Node(value, _head);
    ++_size;
}

void LinkedList::remove(const size_t pos)
{
    if (pos >= _size)
        throw std::out_of_range("out_of_range");
    if (pos == 0)
    {
        removeFront();
        return;
    }
    if (pos == this->_size - 1)
    {
        removeBack();
        return;
    }
    Node *curr = getNode(pos - 1);
    removeNextNode(curr);
    return;
}

void LinkedList::removeNextNode(Node* node)
{
    if (node->next != nullptr)
    {
        node->removeNext();
        _size--;
    }
    return;
}

void LinkedList::removeBack()
{
    Node *curr = getNode(_size - 2);
    delete curr->next;
    curr->next = nullptr;
    _size--;
}

void LinkedList::removeFront()
{
    Node *newHead = _head;
    _head = _head->next;
    delete newHead;
    _size--;
}

long long int LinkedList::findIndex(const ValueType& value) const
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

typename LinkedList::Node* LinkedList::findNode(const ValueType& value) const
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

void LinkedList::reverse()
{
    Node *prev = NULL;
    Node *curr = _head;
    Node *next = _head->next;
    while (next != NULL)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = curr->next;
    }
    curr->next = prev;
    _head = curr;
    return;
}

LinkedList LinkedList::reverse() const
{
    LinkedList l = *this;
    return l.getReverseList();
}

LinkedList LinkedList::getReverseList()
{
    LinkedList *l = new LinkedList;
    *l = *this;
    l->reverse();
    return *l;
}

size_t LinkedList::size() const
{
    return _size;
}

void LinkedList::forceNodeDelete(Node* node)
{
    if (node == nullptr) {
        return;
    }
    
    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}
*/
