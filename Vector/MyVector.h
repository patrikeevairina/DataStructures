#ifndef MYVECTOR_H
#define MVECTOR_H

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cstring>

#define ValueType double

enum class ResizeStrategy {
    Additive,
    Multiplicative
};

enum class SortedStrategy
{
    Increase,
    Decrease
};

class MyVector
{
public:
    MyVector(size_t size = 0, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f); 
    MyVector(size_t size, ValueType value = ValueType(), ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
    
    MyVector(const MyVector& copy);
    MyVector& operator=(const MyVector& copy);
    
    ~MyVector();
    
    size_t capacity() const;
    size_t size() const;
    float loadFactor();
    
    ValueType& operator[](const size_t i);//+
    const ValueType& operator[](const size_t i) const;
    
    void pushBack(const ValueType& value);//+
    void pushFront(const ValueType& value);
    void insert(const size_t i, const ValueType& value);
    void insert(const size_t i, const MyVector& value);
    void popBack();
    void erase(const size_t i);
    void erase(const size_t i, const size_t len);
    size_t find(const ValueType& value, bool isBegin = true) const;
    void reserve(const size_t capacity);
    void resize(const size_t size, const ValueType value = 0.0);
    void frameVector();
    void clear(); //+
    
    class Iterator
    {
    public:
        Iterator(ValueType *it): ptr(it) {}
        ValueType& operator*(){return *ptr;}
        ValueType* operator->(){return ptr;}
        Iterator operator++ () { return ++ptr; }
        Iterator operator-- () { return --ptr; }
        bool operator==(const Iterator &i) {return ptr == i.ptr;}
        bool operator!=(const Iterator &i) {return ptr != i.ptr;}
        bool operator<(Iterator& b) { return ptr < b.ptr; };
        bool operator>(Iterator& b) { return ptr > b.ptr; };
    protected:
        ValueType *ptr;
    };
    
    Iterator begin(){return Iterator(_data);};
    Iterator end(){return Iterator(_data+_size);};
    
    MyVector sortedSquares(SortedStrategy = SortedStrategy::Increase);
    
private:
    ValueType* _data;
    size_t _size;
    size_t _capacity;
    float _coef; 
    ResizeStrategy _strategy;
};

#endif // VECTOR_H
