#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <cstdlib>

template <typename ValueType>
class LinkedList
{
    // класс узла списка
    // по своей сути, может содержать любые данные,
    // можно реализовать и ассоциативный массив, просто добавив
    // поле с ключем в узел и, с учетом этого, поменять методы LinkedList
    // (доступ по ключу, поиск по ключу и т.д.)
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
    ////
    LinkedList();
    LinkedList(const LinkedList& copyList);
    LinkedList& operator=(const LinkedList& copyList);

    LinkedList(LinkedList&& moveList) noexcept;
    LinkedList& operator=(LinkedList&& moveList) noexcept;

    ~LinkedList();
    ////

    // доступ к значению элемента по индексу
    const ValueType& operator[](const size_t pos) const;
    ValueType& operator[](const size_t pos);
    // доступ к узлу по индексу
    LinkedList::Node* getNode(const size_t pos) const;
    LinkedList::Node* getNode(const size_t pos);

    // вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
    void insert(const size_t pos, const ValueType& value);
    // вставка элемента после узла, (O(1))
    void insertAfterNode(Node* node, const ValueType& value);
    // вставка в конец (О(n))
    void pushBack(const ValueType& value);
    // вставка в начало (О(1))
    void pushFront(const ValueType& value);

    // удаление
    void remove(const size_t pos);
    void removeNextNode(Node* node);
    void removeFront();
    void removeBack();

    // поиск, О(n)
    long long int findIndex(const ValueType& value) const;
    Node* findNode(const ValueType& value) const;

    // разворот списка
    void reverse();						// изменение текущего списка
    LinkedList reverse() const;			// полчение нового списка (для константных объектов)
    LinkedList getReverseList() ;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список

    size_t size() const;

};

template <typename ValueType>
LinkedList<ValueType>::Node::Node(const ValueType& value, Node* next)
{
    this->value = value;
    this->next = next;
}

template <typename ValueType>
LinkedList<ValueType>::Node::~Node()
{
    // ничего не удаляем, т.к. агрегация
}

template <typename ValueType>
void LinkedList<ValueType>::Node::insertNext(const ValueType& value)
{
    Node* newNode = new Node(value, this->next);
    this->next = newNode;
}

template <typename ValueType>
void LinkedList<ValueType>::Node::removeNext()
{
    Node* removeNode = this->next;
    if (this->next == nullptr)
        return;
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
}

template <typename ValueType>
LinkedList<ValueType>::LinkedList()
    : _head(nullptr), _size(0)
{

}

template <typename ValueType>
LinkedList<ValueType>::LinkedList(const LinkedList& copyList)//norm
{
    this->_size = copyList._size;
    this->_head = new Node(copyList._head->value);
    Node *currCopy = copyList._head;
    Node *curr = this->_head;

    while (currCopy->next != nullptr)
    {
        curr->next = new Node(currCopy->next->value);
        //        std::cout << currCopy->next->value << ", " ;
        curr = curr->next;
        currCopy = currCopy->next;
    }
}

template <typename ValueType>
LinkedList<ValueType>& LinkedList<ValueType>::operator=(const LinkedList& copyList)//okay
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

template <typename ValueType>
LinkedList<ValueType>::LinkedList(LinkedList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->_head = moveList._head;

    moveList._size = 0;
    moveList._head = nullptr;
}

template <typename ValueType>
LinkedList<ValueType>& LinkedList<ValueType>::operator=(LinkedList&& moveList) noexcept
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

template <typename ValueType>
LinkedList<ValueType>::~LinkedList()
{
    forceNodeDelete(_head);
}

template <typename ValueType>
const ValueType& LinkedList<ValueType>::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

template <typename ValueType>
ValueType& LinkedList<ValueType>::operator[](const size_t pos)
{
    return getNode(pos)->value;
}

template <typename ValueType>
typename LinkedList<ValueType>::Node* LinkedList<ValueType>::getNode(const size_t pos) const
{
    if (pos >= _size)
        throw std::out_of_range("error");
    Node* bufNode = this->_head;
    for (size_t i = 0; i < pos; ++i)
    {
        bufNode = bufNode->next;
    }
    return bufNode;
}

template <typename ValueType>
typename LinkedList<ValueType>::Node* LinkedList<ValueType>::getNode(const size_t pos)
{

    if (pos >= _size)
        throw std::out_of_range("error");
    Node* bufNode = this->_head;
    for (size_t i = 0; i < pos; ++i)
    {
        bufNode = bufNode->next;
    }
    return bufNode;
}


template <typename ValueType>
void LinkedList<ValueType>::insert(const size_t pos, const ValueType& value)
{
    if (pos > _size)
        throw std::out_of_range("error");
    if (pos == 0) {
        pushFront(value);
    }
    else {
        Node* bufNode = this->_head;
        for (size_t i = 0; i < pos-1; ++i) {
            bufNode = bufNode->next;
        }
        bufNode->insertNext(value);
        ++_size;
    }
}

template <typename ValueType>
void LinkedList<ValueType>::insertAfterNode(Node* node, const ValueType& value)
{
    node->insertNext(value);
    _size++;
}

template <typename ValueType>
void LinkedList<ValueType>::pushBack(const ValueType& value)
{
    if (_size == 0) {
        pushFront(value);
        return;
    }
    insert(_size, value);
}

template <typename ValueType>
void LinkedList<ValueType>::pushFront(const ValueType& value)
{
    _head = new Node(value, _head);
    ++_size;
}

template <typename ValueType>
void LinkedList<ValueType>::remove(const size_t pos)
{
    if (pos >= _size)
        throw std::out_of_range("error");
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

template <typename ValueType>
void LinkedList<ValueType>::removeNextNode(Node* node)
{
    if (node->next != nullptr)
    {
        node->removeNext();
        _size--;
    }
    return;
}

template <typename ValueType>
void LinkedList<ValueType>::removeBack()
{
    Node *curr = getNode(_size - 2);
    delete curr->next;
    curr->next = nullptr;
    _size--;
}

template <typename ValueType>
void LinkedList<ValueType>::removeFront()
{
    Node *newHead = _head->next;
    _head = newHead;
    _size--;
}

template <typename ValueType>
long long int LinkedList<ValueType>::findIndex(const ValueType& value) const
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
typename LinkedList<ValueType>::Node* LinkedList<ValueType>::findNode(const ValueType& value) const
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
void LinkedList<ValueType>::reverse()
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

template <typename ValueType>
LinkedList<ValueType> LinkedList<ValueType>::reverse() const
{
    LinkedList l = *this;
    return l.getReverseList();
}

template <typename ValueType>
LinkedList<ValueType> LinkedList<ValueType>::getReverseList()
{
    LinkedList *l = new LinkedList;
    *l = *this;
    l->reverse();
    return *l;
}

template <typename ValueType>
size_t LinkedList<ValueType>::size() const
{
    return _size;
}

template <typename ValueType>
void LinkedList<ValueType>::forceNodeDelete(Node* node)
{
    if (node == nullptr) {
        return;
    }

    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}

#endif // LINKEDLIST_H

