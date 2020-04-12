#include "vector.h"

#include <iostream>
#include <cassert>
#include <cstring>
#include <cmath>

MyVector::MyVector(size_t size, ResizeStrategy ResizeStrategy, float coef, size_t delta)
{
    _size = size;
    _capacity = 1;
    _data = nullptr;

    _strategy = ResizeStrategy;
    if (_strategy == ResizeStrategy::Additive)
        _delta = delta;
    if (_strategy == ResizeStrategy::Multiplicative)
        _coef = coef;
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy ResizeStrategy, float coef, size_t delta)
{

    _capacity = size * coef;
    _size = size;
    _data = new ValueType[_capacity];

    for (size_t i = 0; i < _size; i++)
    {

        _data[i] = value;
    }

    _strategy = ResizeStrategy;

    if (_strategy == ResizeStrategy::Additive)
        _delta = delta;
    if (_strategy == ResizeStrategy::Multiplicative)
        _coef = coef;
}

MyVector::MyVector(const MyVector& copy)
{

    _size = copy._size;

    _capacity = copy._capacity;

    _data = new ValueType[_capacity];

    memcpy(_data, copy._data, sizeof(ValueType)*(_size));

    _strategy = copy._strategy;
    if (_strategy == ResizeStrategy::Additive)
        _delta = copy._delta;
    if (_strategy == ResizeStrategy::Multiplicative)
        _coef = copy._coef;
}

MyVector& MyVector::operator=(const MyVector& copy)
{
    if (this == &copy)
    {
        return *this;
    }
    MyVector bufVector(copy);
    this->_size = bufVector._size;

    this->_capacity = bufVector._capacity;

        this->_data = new ValueType[_capacity];
    if (bufVector._data != nullptr)
        memcpy(this->_data, bufVector._data, (this->_size) * sizeof (ValueType));
    else
        this->_data = nullptr;


    std::cout << "Begin" << std::endl;
    for (ValueType *i = bufVector.begin(); i < bufVector.end(); i++)
        std::cout << *i << ", ";
    std::cout << "End" << std::endl;

    this->_strategy = bufVector._strategy;
    if (_strategy == ResizeStrategy::Additive)
        _delta = bufVector._delta;
    if (_strategy == ResizeStrategy::Multiplicative)
        _coef = bufVector._coef;

    return *this;
}

MyVector::~MyVector()
{
    if (_data != nullptr)
    {
        delete[] this->_data;
        this->_data = nullptr;
    }
    _size = 0;
    _capacity = 0;
//    std::cout << "Removing" << std::endl;
}

size_t MyVector::capacity() const
{
    return this->_capacity;
}

size_t MyVector::size() const
{
    return this->_size;
}

float MyVector::loadFactor()
{
    float t = (float)_size;
    float s = (float)_capacity;
    return t/s;
}

ValueType& MyVector::operator[](const size_t i) const
{
    if (i >= this->_size)
        assert(i >= this->_size);
    ValueType &res = _data[i];

    return res;
}

void MyVector::reserve(const size_t capacity)
{
//    if (loadFactor() < 1)
//        return;

    _capacity = (_capacity == 0) ? 1 : _capacity;
//    if (_strategy == ResizeStrategy::Additive)
//    {

//    }
//    if (_strategy == ResizeStrategy::Multiplicative)
//    {

//    }
    _capacity = capacity;
    std::cout << " new Cap " << _capacity << std::endl;

    if (_data == nullptr)
        _data = new ValueType[_capacity];
    else
    {
        ValueType *newData = new ValueType[_capacity];
        memcpy(newData, _data, _size * sizeof(ValueType));
        _data = newData;
    }

}

void MyVector::pushBack(const ValueType &value)
{
    if (loadFactor() == 1)
    {
        if (_strategy == ResizeStrategy::Multiplicative)
            reserve(_capacity * _coef);
        if (_strategy == ResizeStrategy::Additive)
            reserve(_capacity+_delta);
    }
    this->_data[_size] = value;
    _size++;
    return;
}



void MyVector::insert(const size_t i, const ValueType &value)
{
    if (i > _size)
        return;
 //       std::cout << _size << " " << _capacity;

    if (loadFactor() >= 1)
    {
        if (_strategy == ResizeStrategy::Multiplicative)
            reserve(_size * _coef);
        if (_strategy == ResizeStrategy::Additive)
            reserve(_capacity+_delta);
    }

    ValueType *copy = new ValueType[this->_size + 1];
    memcpy(copy, this->_data, sizeof(ValueType) * i);
    copy[i] = value;

    for (size_t k = i; k < this->_size; k++)
    {
        copy[k+1] = this->_data[k];
    }
    if (this->_data != nullptr)
        delete[] this->_data;
    this->_data = copy;

    _size++;
    frameVector();
    return;
}

void MyVector::insert(const size_t i, const MyVector &value)
{
    if (i > _size)
        return;
    _size += value._size;
//    std::cout << _size << " " << _capacity;
    if (loadFactor() > 1)
    {
        if (_strategy == ResizeStrategy::Additive)
        {
            while (loadFactor() > 1)
            {
                reserve(_capacity + _delta);
            }
        }
        if (_strategy == ResizeStrategy::Multiplicative)
        {
            while (loadFactor() > (1 / (_coef)*(_coef)))
            {
                reserve(_capacity * _coef);
                    std::cout << "num1: " << capacity() << " " << size() << std::endl;
            }
        }

    }
    _size -= value._size;
    ValueType *copy = new ValueType[this->_size + value._size];
    memcpy(copy, this->_data, sizeof(ValueType)*i);

    for (size_t k = i; k < value._size + i; k++)
    {
        copy[k] = value._data[k - i];
    }

    for (size_t k = i + value._size; k < _size + value._size; k++)
    {
        copy[k] = this->_data[k - value._size];
    }

    if (_data != nullptr)
        delete[] this->_data;
    this->_data = copy;

    _size += value._size;
    
    frameVector();

    return;
}

void MyVector::popBack()
{
    if (this->_data == nullptr)
        return;

    ValueType *copy = new ValueType[size() - 1];
    memcpy(copy, this->_data, sizeof(ValueType) * (size() - 1));
    delete[] this->_data;
    this->_data = copy;
    frameVector();
    _size--;
}

void MyVector::erase(const size_t i)
{
    if (this->_data == nullptr)
        return;

    for (size_t k = i; k < size() - 1; k++)
    {
        this->_data[k] = this->_data[k+1];
    }
    _size--;
    frameVector();
    return;
}

void MyVector::erase(const size_t i, const size_t len)
{
    if ((i + len) > size())
        return;
    for (size_t k = i; k < size() - len; k++)
    {
        this->_data[k] = this->_data[k+len];
    }
    _size += -len;
    frameVector();
    return;
}

size_t MyVector::find(const ValueType &value, bool isBegin) const
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
        for (size_t i = size() - 1; i >= 0; i--)
        {
            if (this->_data[i] == value)
                return i;
        }

    }
    return -1;
}


void MyVector::resize(const size_t size, const ValueType value)
{
    if (size > _size)
    {
        size_t oldSize = _size;
        _size = size;
        if (loadFactor() > 1)
        {
            if (_strategy == ResizeStrategy::Additive)
            {
                size_t newDelta = size - _capacity;
                reserve(_capacity + newDelta);
            }

            if (_strategy == ResizeStrategy::Multiplicative)
            {
                reserve(size);
            }
            std::cout << _size << " - " << _capacity << std::endl;
        }

        ValueType *copy = new ValueType[oldSize];
        if (_data != nullptr)
        {
            memcpy(copy, this->_data, sizeof(ValueType) * oldSize);

            delete[] this->_data;
        }

        _data = new ValueType[_size];
        for (size_t i = 0; i < oldSize; i++)
        {
            _data[i] = copy[i];

        }
        for (size_t i = oldSize; i < _size; i++)
        {
            _data[i] = value;
        }
    }

    if (size == _size)
        return;
    if (size < _size)
    {
        ValueType *copy = new ValueType[size];
        memcpy(copy, _data, sizeof(ValueType) * size);
        delete[] this->_data;
        this->_data = copy;
        _size = size;
        _capacity = _size;
    }
}

void MyVector::frameVector()
{
    if (_strategy == ResizeStrategy::Additive)
    {
        if (loadFactor() < (float)(_capacity - _delta) / (float)(_capacity))
        {

            if (_data != nullptr)
            {
                ValueType *copy = new ValueType[_size + _delta];
                memcpy(copy, _data, _size *sizeof (ValueType));
                delete [] _data;
                _data = copy;
                _capacity = _size + _delta;
            }
            if (_data == nullptr)
            {
                delete [] _data;
                _data = new ValueType[_size + _delta];
                _capacity = _size + _delta;
            }
        }
        return;
    }

    if (_strategy == ResizeStrategy::Multiplicative)
    {
        if (loadFactor() < 1 / (_coef * _coef))
        {
            if (_data != nullptr)
            {
                ValueType *copy = new ValueType[(size_t)((float)(_size * _coef * _coef))];
                memcpy(copy, _data, _size *sizeof (ValueType));
                delete [] _data;
                _data = copy;
                _capacity = (size_t)((float)(_size * _coef * _coef));
            }
            if (_data == nullptr)
            {
                delete [] _data;
                _data = new ValueType[(size_t)((float)(_size * _coef * _coef))];
                _capacity = (size_t)((float)(_size * _coef * _coef));
            }
            return;
        }
    }
}

void MyVector::clear()
{
    delete[] _data;
    _size = 0;
}

ValueType* MyVector::begin()
{
    return this->_data;
}

ValueType* MyVector::end()
{
    return this->_data+size();
}

MyVector MyVector::sortedSquares(const MyVector &vec, bool SortedStrategy)
{
    MyVector *sorted = new MyVector;
    sorted->_size = vec._size;
    sorted->_capacity = vec._capacity;
    sorted->_strategy = vec._strategy;
    if (sorted->_strategy == ResizeStrategy::Additive)
        _delta = vec._delta;
    if (sorted->_strategy == ResizeStrategy::Multiplicative)
        _coef = vec._coef;
    sorted->_data = new ValueType[sorted->_capacity];
    if (SortedStrategy == true)
    {
        size_t idx1 = 0;
        size_t idx2 = vec._size - 1;

        for (size_t i = 0; i < vec._size ; i++)
        {
 
            if (idx1 == idx2)
            {
                sorted->_data[vec._size - i - 1] = (vec._data[idx2])*(vec._data[idx2]);
            }

            if (idx1 != idx2)
            {

                if (abs(vec._data[idx1]) >= abs(vec._data[idx2]))
                {
                    sorted->_data[vec._size - i - 1] = vec._data[idx1]*vec._data[idx1];                  
                    idx1++;
                }
                else /*if (abs(vec._data[idx1]) < abs(vec._data[idx2]))*/
                {
                    sorted->_data[vec._size - i - 1] = (vec._data[idx2])*(vec._data[idx2]);    
                    idx2--;
                }             
            }
        }
    }
    return  *sorted;
}

