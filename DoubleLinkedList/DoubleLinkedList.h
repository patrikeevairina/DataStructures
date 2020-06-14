#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
#define ValueType double

class DoubleLinkedList
{
    struct Node {
        Node(const ValueType& value, Node* next = nullptr, Node *previous = nullptr);//+
        ~Node();

        void insertNext(const ValueType& value);//+
        void removeNext();//+

        ValueType value;
        Node* previous;
        Node* next;

    };

public:
    DoubleLinkedList();//+
    DoubleLinkedList(const DoubleLinkedList& copyList);//+
    DoubleLinkedList& operator=(const DoubleLinkedList& copyList);//
    ~DoubleLinkedList();

    // доступ к значению элемента по индексу
    ValueType& operator[](const size_t pos);//+
    const ValueType& operator[](const size_t pos) const;
    // доступ к узлу по индексу
    DoubleLinkedList::Node* getNode(const size_t pos) const;//+

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
    DoubleLinkedList reverse() const;			// полчение нового списка (для константных объектов)// не хватило мозгов на осмысление этого метода
    DoubleLinkedList getReverseList();	// чтобы неконстантный объект тоже мог возвращать новый развернутый список//на осмысление этого тоже не хватило:(

    size_t size() const;
private:
    Node* _tail;
    Node*	_head;
    size_t	_size;

    void forceNodeDelete(Node* node);
};

#endif
