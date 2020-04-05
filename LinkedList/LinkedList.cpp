#include "LinkedList.h"

#include <cassert>


template<typename T>
LinkedList<T>::Node::Node(const T& value, Node *next)
{
    this->value = value;
    this->next = next;
}
template<typename T>
LinkedList<T>::Node::~Node(){}

template<typename T>
void LinkedList<T>::Node::insertNext(const T& value)
{
    Node *newNode = new Node(value, this->next);
    this->next = newNode;
}

template<typename T>
void LinkedList<T>::Node::removeNext()
{
    Node *removeNode = this->next;
    Node *newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
}

template<typename T>
LinkedList<T>::LinkedList()
    :_head(nullptr), _size(0)
{

}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& copyList)
{
    this->_size = copyList._size;
    if (this->_size == 0)
    {
        this->_head = nullptr;
        return;
    }

    this->_head = new Node(copyList._head->value);
    Node *currentNode = this->_head;
    Node *currentCopyNode = copyList._head;

    while (currentCopyNode->next)
    {
        currentNode->next = new Node(currentCopyNode->value);
        currentCopyNode = currentCopyNode->next;
        currentNode = currentNode->next;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& copyList)
{
    if (this == &copyList)
        return *this;

    LinkedList bufList(copyList);
    this->_size = bufList._size;
    this->_head = bufList._head;

    return *this;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->head = moveList._head;

    moveList._size = 0;
    moveList._head = nullptr;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& moveList) noexcept
{
    if (this == &moveList)
        return *this;
    forceNodeDelete(_head);
    this->_size = moveList._size;
    this->_head = moveList._head;

    moveList._size = 0;
    moveList._head = nullptr;

    return *this;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    forceNodeDelete(_head);
}

template<typename T>
T& LinkedList<T>::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(const size_t pos) const
{
    if (pos < 0)
        assert(pos < 0);
    else if (pos >= this->_size)
        assert(pos >= this->_size);

    Node *current = this->_head;
    for (size_t i = 0; i < pos; i++)
    {
        current = current->next;
    }

    return current;
}

template<typename T>
void LinkedList<T>::insert(const size_t pos, const T& value)
{
    if (pos < 0)
        assert(pos < 0);
    else if (pos > this->_size)
        assert(pos > this->_size);
    if (pos == 0)
    {
        pushFront(value);
        return;
    }
    else
    {
       Node *current = this->_head;
       for (size_t k = 0; k < pos - 1; k++)
       {
          current = current->next;
       }
       current->insertNext(value);
       ++_size;
    }
}

template<typename T>
void LinkedList<T>::insertAfterNode(Node *node, const T& value)
{
    node->insertNext(value);
}

template<typename T>
void LinkedList<T>::pushBack(const T& value)
{
    if (this->_size == 0)
    {
        pushFront(value);
        return;
    }
    insert(this->_size, value);
}

template<typename T>
void LinkedList<T>::pushFront(const T& value)
{
    _head = new Node(value, this->_head);
    this->_size++;
}

template<typename T>
void LinkedList<T>::remove(const size_t pos) //норм: работает на 0, последнем элементе и всех промежуточных
{
    if (pos < 0)
        assert(pos < 0);
    else if (pos >= this->_size)
        assert(pos >= this->_size);
    if (pos == 0)
    {
        removeFront();
        _size--;
        return;
    }
    if (pos == this->_size - 1)
    {
        removeBack();
        _size--;
        return;
    }

    Node *prev = getNode(pos - 1);
    prev->removeNext();
    _size--;

}

template<typename T>
void LinkedList<T>::removeNextNode(Node *node)//не работает (работает)
{
    node->removeNext();
}

template<typename T>
void LinkedList<T>::removeFront()
{
    if (this->_size == 1)
    {
        delete _head;
        return;
    }
    Node *current = _head;
    current = current->next;
    _head = current;
}

template<typename T>
void LinkedList<T>::removeBack()
{
    if (this->_size == 1)
    {
        delete _head;
        return;
    }
    Node *curr = getNode(this->_size - 2);
    delete curr->next;
    curr->next = nullptr;
}

template<typename T>
size_t LinkedList<T>::findIndex(const T& value) const
{
    Node *current = _head;
    size_t pos = 0;
    while (current->next)
    {
        if (current->value == value)
            return pos;
        current = current->next;
        pos++;
    }
    if (current->value == value)
        return pos;
    if (pos == this->_size - 1)
        return -1;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::findNode(const T& value) const
{
    Node *current = this->_head;
    while (current->next)
    {
        if (current->value == value)
            return current;
        current = current->next;
    }
    if (current->value == value)
        return current;
    if (current->value != value)
        assert(current->value != value);
}

template<typename T>
void LinkedList<T>::reverse()
{
    if (this->_size == 1)
        return;
    Node *prev = nullptr;
    Node *curr = _head;
    Node *next = _head->next;
    while (next != nullptr)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = curr->next;
    }
    curr->next = prev;
    _head = curr;
}

template<typename T>
typename LinkedList<T>::LinkedList LinkedList<T>::reverse() const
{
    LinkedList c = new LinkedList;
    if (this->_size == 1)
    {
        c._head = this->_head;
        return c;
    }
    c._head = this->_head;
    c._size = this->_size;
    Node *prev = nullptr;
    Node *curr = c._head;
    Node *next = c._head->next;
    while (next != nullptr)
        {
                curr->next = prev;
                prev = curr;
                curr = next;
                next = curr->next;
        }
        curr->next = prev;
        c._head = curr;
    return c;
}

template<typename T>
size_t LinkedList<T>::size() const
{
    return _size;
}

template<typename T>
void LinkedList<T>::forceNodeDelete(Node* node)
{
    if (node == nullptr)
        return;
    Node *nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}
