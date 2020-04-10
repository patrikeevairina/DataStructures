#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>

using ValueType = double;

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
    List& operator=(const List& copyList);//какая-то приколюха, не работает

    List(List&& moveList) noexcept;
    List& operator=(List&& moveList) noexcept;

    ~List();
    ////

    // доступ к значению элемента по индексу
    ValueType& operator[](const size_t pos) const;//+
    // доступ к узлу по индексу
    List::Node* getNode(const size_t pos) const;//+

    // вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
    void insert(const size_t pos, const ValueType& value);//+
    // вставка элемента после узла, (O(1))
    static void insertAfterNode(Node* node, const ValueType& value);
    // вставка в конец (О(n))
    void pushBack(const ValueType& value);
    // вставка в начало (О(1))
    void pushFront(const ValueType& value);//+

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
    List reverse1() const;			// полчение нового списка (для константных объектов)// не хватило мозгов на осмысление этого метода
    List getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список//на осмысление этого тоже не хватило:(

    size_t size() const;
private:
    Node* _tail;
    Node*	_head;
    size_t	_size;

    void forceNodeDelete(Node* node);
};



#endif // LIST_H
