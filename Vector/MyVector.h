#ifndef MYVECTOR_H
#define MVECTOR_H

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cstring>

//#define ValueType double

enum class ResizeStrategy {
    Additive,
    Multiplicative
};

enum class SortedStrategy
{
    Increase,
    Decrease
};

template <typename ValueType>
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

template <typename ValueType>
MyVector<ValueType>::MyVector(size_t size, ResizeStrategy ResizeStrategy, float coef)
{
    _size = size;
    _strategy = ResizeStrategy;
    _capacity = (_strategy == ResizeStrategy::Multiplicative) ? (size * coef) : (size + coef);
    _capacity = (_capacity == 0) ? 1 : _capacity;
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = ValueType();
    }
    _coef = coef;
}

template <typename ValueType>
MyVector<ValueType>::MyVector(size_t size, ValueType value, ResizeStrategy ResizeStrategy, float coef)
{
    _strategy = ResizeStrategy;
    _capacity = (_strategy == ResizeStrategy::Multiplicative) ? (size * coef) : (size + coef);
    _size = size;
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = value;
    }
    _coef = coef;
}

template <typename ValueType>
MyVector<ValueType>::MyVector(const MyVector& copy)
{
    _size = copy._size;
    _capacity = copy._capacity;
    _data = new ValueType[_capacity];
    memcpy(_data, copy._data, sizeof(ValueType)*(_size));
    _strategy = copy._strategy;
    _coef = copy._coef;
}

template <typename ValueType>
MyVector<ValueType>& MyVector<ValueType>::operator=(const MyVector& copy)
{
    if (this == &copy)
    {
        return *this;
    }
    MyVector bufVector(copy);
    std::swap(this->_size, bufVector._size);
    std::swap(this->_capacity, bufVector._capacity);
    std::swap(_data, bufVector._data);
    std::swap(this->_strategy, bufVector._strategy);
    std::swap(_coef, bufVector._coef);
    return *this;
}

template <typename ValueType>
MyVector<ValueType>::~MyVector()
{
    if (_data != nullptr)
    {
        delete[] this->_data;
        this->_data = nullptr;
    }
    _size = 0;
    _capacity = 0;
}

template <typename ValueType>
size_t MyVector<ValueType>::capacity() const
{
    return this->_capacity;
}

template <typename ValueType>
size_t MyVector<ValueType>::size() const
{
    return this->_size;
}

template <typename ValueType>
float MyVector<ValueType>::loadFactor()
{
    float t = (float)_size;
    float s = (float)_capacity;
    return t/s;
}

template <typename ValueType>
ValueType& MyVector<ValueType>::operator[](const size_t i)
{
    if (i >= _size)
        throw std::out_of_range("position > size");
    ValueType &res = _data[i];
    return res;
}

template <typename ValueType>
const ValueType& MyVector<ValueType>::operator[](const size_t i) const
{
    if (i >= _size)
        throw std::out_of_range("position > size");
    ValueType &res = _data[i];
    return res;
}

template <typename ValueType>
void MyVector<ValueType>::reserve(const size_t capacity)
{
    if (capacity < _size)
        _size = capacity;
    _capacity = capacity;
    if (_data == nullptr)
        _data = new ValueType[_capacity];
    else
    {
        ValueType *newData = new ValueType[_capacity];
        memcpy(newData, _data, _size * sizeof(ValueType));
        delete[] _data;
        _data = newData;
    }
}

template <typename ValueType>
void MyVector<ValueType>::pushBack(const ValueType &value)
{
    if (loadFactor() == 1)
    {
        if (_strategy == ResizeStrategy::Multiplicative)
            reserve(_capacity * _coef * _coef);
        if (_strategy == ResizeStrategy::Additive)
            reserve(_capacity+_coef);
    }
    this->_data[_size] = value;
    _size++;
    return;
}

template <typename ValueType>
void MyVector<ValueType>::insert(const size_t pos, const ValueType &value)
{
    if (pos > _size)
        throw std::out_of_range("out of range");
    if (loadFactor() >= 1)
    {
        if (_strategy == ResizeStrategy::Multiplicative)
            reserve(_size * _coef *_coef);
        if (_strategy == ResizeStrategy::Additive)
            reserve(_capacity+_coef);
    }
    if (pos == _size)
    {
        pushBack(value);
        return;
    }
    for (size_t i = _size; i > pos; i--)
    {
        _data[i] = _data[i-1];
    }
    _data[pos] = value;
    _size++;
    frameVector();
    return;
}

template <typename ValueType>
void MyVector<ValueType>::insert(const size_t i, const MyVector &value)
{
    if (i > _size)
        throw std::out_of_range("out of range");
    if ((_size + value._size) >= _capacity)
    {
        if (_strategy == ResizeStrategy::Multiplicative)
            reserve((_size + value._size)*_coef);
        else
            reserve((_size + value._size)+_coef);
    }
    for (size_t k = i; k < _size; k++)
    {
        _data[k+value._size] = _data[k];
    }
    for (size_t k = i; k < value._size+i; k++)
    {
        _data[k] = value._data[k - i];
    }
    _size += value._size;
    return;
}

template <typename ValueType>
void MyVector<ValueType>::popBack()
{
    if (this->_data == nullptr)
        throw std::invalid_argument("invalid argument");
    _size--;
    frameVector();
}

template <typename ValueType>
void MyVector<ValueType>::erase(const size_t i)
{
    if (this->_data == nullptr)
        return;
    for (size_t k = i; k < size() - 1; k++)
    {
        this->_data[k] = this->_data[k+1];
    }
    _size--;
    frameVector();
    if (capacity() == 0)
        reserve(1);
    return;
}

template <typename ValueType>
void MyVector<ValueType>::erase(const size_t i, const size_t len)
{
    if ((i+len > _size)||(_size == 0))
        throw std::out_of_range("out of range");
    for (size_t k = i; k < size() - len; k++)
    {
        this->_data[k] = this->_data[k+len];
    }
    _size -= len;
    frameVector();
    if (capacity() == 0)
        reserve(1);
    return;
}

template <typename ValueType>
size_t MyVector<ValueType>::find(const ValueType &value, bool isBegin) const
{
    if (isBegin == true)
    {
        for (size_t i = 0; i < size(); i++)
        {
            if (this->_data[i] == value)
                return  i;
        }
    }
    else
    {
        for (size_t i = size(); i >= 0; i--)
        {
            if (this->_data[i-1] == value)
                return i;
        }
    }
    return -1;
}

template <typename ValueType>
void MyVector<ValueType>::resize(const size_t size, const ValueType value)
{
    if (size > _capacity)
    {
        reserve(size*_coef);
        for (size_t i = _size; i < size; i++)
        {
            _data[i] = value;
        }
        _size = size;
        frameVector();
    }
    if (size == _capacity)
        return;
    if (size < _capacity)
    {
        reserve(size*_coef);
        _size = size;
    }
    return;
}

template <typename ValueType>
void MyVector<ValueType>::frameVector()
{
    if (_strategy == ResizeStrategy::Multiplicative)
    {
        if (loadFactor() >= 1 / (_coef * _coef))
        {
            return;
        }
        _capacity = (size_t)((float)(_size * _coef * _coef));
        if (_data != nullptr)
        {
            ValueType *newData = new ValueType[_capacity];
            memcpy(newData, _data, _size * sizeof (ValueType));
            delete[] _data;
            _data = newData;
        }
        else
        {
            _data = new ValueType[_capacity];
        }
    }
    else
    {
        if (loadFactor() >= (float)(_capacity - _coef) / (float)(_capacity))
        {
            return;
        }
        _capacity = _size+_coef;
        if (_data != nullptr)
        {
            ValueType *newData = new ValueType[_capacity];
            memcpy(newData, _data, _size * sizeof (ValueType));
            delete[] _data;
            _data = newData;
        }
        else
        {
            _data = new ValueType[_capacity];
        }
    }
    if (size() == 0)
        reserve(1);

}

template <typename ValueType>
void MyVector<ValueType>::clear()
{
    delete[] _data;
    _size = 0;
    _capacity = 0;
}

template <typename ValueType>
MyVector<ValueType> MyVector<ValueType>::sortedSquares(SortedStrategy strategy) // norm
{
    MyVector sorted = *this;
    size_t idx1 = 0;
    size_t idx2 = this->_size - 1;

    for (size_t i = 0; i < this->_size ; i++)
    {

        if (idx1 == idx2)
        {
            if (strategy == SortedStrategy::Increase)
                sorted._data[this->_size - i - 1] = (this->_data[idx2])*(this->_data[idx2]);
            else
                sorted._data[i] = (this->_data[idx2])*(this->_data[idx2]);
        }

        if (idx1 != idx2)
        {

            if (abs(this->_data[idx1]) >= abs(this->_data[idx2]))
            {
                if (strategy == SortedStrategy::Increase)
                    sorted._data[this->_size - i - 1] = this->_data[idx1]*this->_data[idx1];
                else
                    sorted._data[i] = this->_data[idx1]*this->_data[idx1];
                idx1++;
            }
            else /*if (abs(vec._data[idx1]) < abs(vec._data[idx2]))*/
            {
                if (strategy == SortedStrategy::Increase)
                    sorted._data[this->_size - i - 1] = (this->_data[idx2])*(this->_data[idx2]);
                else
                    sorted._data[i] = (this->_data[idx2])*(this->_data[idx2]);
                idx2--;
            }
        }
    }
    return  sorted;
}


#endif // VECTOR_H
