#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>


template <typename ValueType>
class List
{
    // класс узла списка
    // по своей сути, может содержать любые данные,
    // можно реализовать и ассоциативный массив, просто добавив
    // поле с ключем в узел и, с учетом этого, поменять методы LinkedList
    // (доступ по ключу, поиск по ключу и т.д.)
    struct Node {
        Node(const ValueType& value, Node* next = nullptr, Node *previous = nullptr);//+
        ~Node();

        void insertNext(const ValueType& value);//+
        void removeNext();//+

        ValueType value;
        Node* next;
        Node* previous;
    };

public:
    ////
    List();//+
    List(const List& copyList);//+
    List& operator=(const List& copyList);//



    ~List();
    ////

    // доступ к значению элемента по индексу
    ValueType& operator[](const size_t pos);//+
    const ValueType& operator[](const size_t pos) const;
    // доступ к узлу по индексу
    List::Node* getNode(const size_t pos) const;//+

    // вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
    void insert(const size_t pos, const ValueType& value);//++
    // вставка элемента после узла, (O(1))
    void insertAfterNode(Node* node, const ValueType& value);
    // вставка в конец (О(n))
    void pushBack(const ValueType& value);//+
    // вставка в начало (О(1))
    void pushFront(const ValueType& value);//+

    // удаление
    void remove(const size_t pos);//i think it's okay but i'm not sure
    void removeNextNode(Node* node);//it must be okay
    void removeFront();//+
    void removeBack();//+, but strange if _size == 1

    // поиск, О(n)
    long long int findIndex(const ValueType& value) const;
    Node* findNode(const ValueType& value) const;

    // разворот списка
    void reverse();		//+				// изменение текущего списка
    List reverse() const;			// полчение нового списка (для константных объектов)// не хватило мозгов на осмысление этого метода
    List getReverseList();	// чтобы неконстантный объект тоже мог возвращать новый развернутый список//на осмысление этого тоже не хватило:(

    size_t size() const;
private:
    Node* _tail;
    Node*	_head;
    size_t	_size;

    void forceNodeDelete(Node* node);
};

template <typename ValueType>
List<ValueType>::Node::Node(const ValueType& value, Node *next, Node *previous)
{
    this->value = value;
    this->next = next;
    this->previous = previous;
    //std::cout << "god" << std::endl;
    //delete previous->next;
    if (previous != nullptr)
        previous->next = this;
    //delete next->previous;
    if (next != nullptr)
        next->previous = this;
    //std::cout << "god" << std::endl;
}

template <typename ValueType>
List<ValueType>::Node::~Node()
{
    //
}

template <typename ValueType>
void List<ValueType>::Node::insertNext(const ValueType &value)//not sure
{
    if (this->next != nullptr)
        Node *newNode = new Node(value, this->next, this);
    else
    {
        Node *newNode = new Node(value, nullptr, this);
    }

}

template <typename ValueType>
void List<ValueType>::Node::removeNext()
{
    Node* removeNode = this->next;
    if (this->next == nullptr)
        return;
    Node* newNext = removeNode->next;
    delete removeNode;
    removeNode = nullptr;
    this->next = newNext;
    newNext->previous = this;
}

template <typename ValueType>
List<ValueType>::List()
    :_tail(nullptr), _head(nullptr), _size(0)
{

}

template <typename ValueType>
List<ValueType>::List(const List& copyList)
{
    //std::cout << "start copy" << std::endl;
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
    //std::cout << currCopy->next->value << std::endl;
    _tail = new Node(currCopy->next->value, nullptr, curr);
    //_tail = curr->next;
    //std::cout << _tail->value << std::endl;
}

template <typename ValueType>
List<ValueType>& List<ValueType>::operator=(const List &copyList)//DONT FORGET
{
    if (this == &copyList)
    {
        return *this;
    }
    List bufList(copyList);
    this->_size = bufList._size;
    if (_head != nullptr)
    {
        //std::cout << "stranna" << std::endl;
        //std::cout << _head->value << " " << _tail->value << std::endl;
        forceNodeDelete(_head);
       // delete _head;
    }
    //std::cout << "now ok" << std::endl;
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

template <typename ValueType>
List<ValueType>::~List()
{
    forceNodeDelete(_head);
    //Node *node = _head;
   // delete _head;
//    while (node->next)
//    {
//        node = node->next;
//        delete node->previous;
//    }
//    delete _tail;
}

template <typename ValueType>
ValueType& List<ValueType>::operator[](const size_t pos)
{
    return getNode(pos)->value;
}

template <typename ValueType>
const ValueType& List<ValueType>::operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

template <typename ValueType>
typename List<ValueType>::Node* List<ValueType>::getNode(const size_t pos) const //working
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

template <typename ValueType>
void List<ValueType>::insert(const size_t pos, const ValueType &value)
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

template <typename ValueType>
void List<ValueType>::pushFront(const ValueType &value)//вроде заработало
{
    if (_head == nullptr)
    {
        //std::cout << "list empty" << std::endl;
        Node *newHead = new Node(value, 0, 0);
        _head = newHead;
        _tail = _head;
        //std::cout << _size << std::endl;
        _size++;
        return;
    }
    Node *newHead = new Node(value, _head, nullptr);
    _head = newHead;
    _size++;

}

template <typename ValueType>
void List<ValueType>::pushBack(const ValueType &value)//working
{
    if (_head == nullptr)
    {
        //std::cout << "okey" << std::endl;
        pushFront(value);
        return;
    }
   // std::cout << "returned from pushFront" << std::endl;
    Node *newTail = new Node(value, nullptr, _tail);
    _tail = newTail;
    _size++;
}

template <typename ValueType>
void List<ValueType>::insertAfterNode(Node *node, const ValueType &value)
{
    node->insertNext(value);
    _size++;
}

template <typename ValueType>
void List<ValueType>::removeBack()//работает на 1 элементе, на нескольких вроде тоже
{
    try
    {
        if (_size == 0)
            throw std::out_of_range("error");
        if (_size == 1)
        {
            std::cout << "okey" << std::endl;
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
    catch(std::out_of_range &e)
    {
        std::cout << "List is empty" << std::endl;
    }
}

template <typename ValueType>
void List<ValueType>::removeFront()
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
template <typename ValueType>
void List<ValueType>::remove(const size_t pos)//вроде ничего не ломает
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

template <typename ValueType>
void List<ValueType>::removeNextNode(Node *node)
{
    if (node->next == nullptr)
        return;
    node->removeNext();
    _size--;
    return;
}

template <typename ValueType>
long long int List<ValueType>::findIndex(const ValueType& value) const
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
typename List<ValueType>::Node* List<ValueType>::findNode(const ValueType &value) const
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
void List<ValueType>::reverse()
{
    if ((_size == 1)||(_size ==0))
        return;
    Node *left = _head;
    Node *right = _tail;
    while (left != right && left->previous != right)
    {
        std::swap(left->value, right->value);
        left = left->next;
        right = right->previous;
    }
}

template <typename ValueType>
List<ValueType> List<ValueType>::reverse() const
{
    List l = *this;
    return l.getReverseList();
}

template <typename ValueType>
List<ValueType> List<ValueType>::getReverseList()
{
    List *l = this;
    l->reverse();
    return *l;
}

template <typename ValueType>
size_t List<ValueType>::size() const
{
    return _size;
}

template <typename ValueType>
void List<ValueType>::forceNodeDelete(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    //Node* nextDeleteNode = node->next;
    node = node->next;
    delete node->previous;
    forceNodeDelete(node);
}




#endif // LIST_H
