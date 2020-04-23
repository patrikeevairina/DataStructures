#include "vector.h"
#include <iostream>
#include <cassert>
#include <cstring>
#include <cmath>

MyVector::MyVector(size_t size, ResizeStrategy ResizeStrategy, float coef)
{
    _size = size;
    _capacity = 1;
    _data = new ValueType[_capacity];
    _strategy = ResizeStrategy;
    _coef = coef;
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy ResizeStrategy, float coef)
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

MyVector::MyVector(const MyVector& copy)
{
    _size = copy._size;
    _capacity = copy._capacity;
    _data = new ValueType[_capacity];
    memcpy(_data, copy._data, sizeof(ValueType)*(_size));
    _strategy = copy._strategy;
    _coef = copy._coef;
}

MyVector& MyVector::operator=(const MyVector& copy)
{
    if (this == &copy)
        {
            return *this;
        }
        MyVector bufVector(copy);
        std::swap(this->_size, bufVector._size);
        std::swap(this->_capacity, bufVector._capacity);
       // this->_data = new ValueType[_capacity];
        //if (bufVector._data != nullptr)
           // memcpy(this->_data, bufVector._data, (this->_size) * sizeof (ValueType));
            std::swap(_data, bufVector._data);
        //else
           // this->_data = nullptr;
        std::swap(this->_strategy, bufVector._strategy);
        std::swap(_coef, bufVector._coef);
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

ValueType& MyVector::operator[](const size_t i)
{
    assert(i >= this->_size);
    ValueType &res = _data[i];
    return res;
}

const ValueType& MyVector::operator[](const size_t i) const
{
    assert(i >= this->_size);
    ValueType &res = _data[i];
    return res;
}

void MyVector::reserve(const size_t capacity)
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

void MyVector::pushBack(const ValueType &value)
{
    if (loadFactor() == 1)
    {
        if (_strategy == ResizeStrategy::Multiplicative)
            reserve(_capacity * _coef);
        if (_strategy == ResizeStrategy::Additive)
            reserve(_capacity+_coef);
    }
    this->_data[_size] = value;
    _size++;
    return;
}



void MyVector::insert(const size_t pos, const ValueType &value)
{
    if (pos > _size)
        assert(pos > _size);

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

void MyVector::insert(const size_t i, const MyVector &value)
{
    if (i > _size)
        assert(i > _size);

    if ((_size + value._size) >= _capacity)
    {
        if (_strategy == ResizeStrategy::Multiplicative)
            reserve((_size + value._size)*_coef*_coef);
        else
            reserve((_size + value._size)+_coef);
    }
    for (size_t k = i; k < _size; k++)
    {
        _data[k+value._size] = _data[k];
    }
    for (size_t k = i; k < value._size; k++)
    {
        _data[k] = value._data[k - i];
    }
    _size += value._size;
    return;
}

void MyVector::popBack()

{
    if (this->_data == nullptr)
        return;

    _data[_size - 1] = 0;
    _size--;
    frameVector();
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
    if (size > _capacity)
    {
        reserve(size);
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
        reserve(size);
        _size = size;
    }
    return;
}

void MyVector::frameVector() 
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


MyVector MyVector::sortedSquares(const MyVector &vec, SortedStrategy strategy) // norm
{
    MyVector *sorted = new MyVector;
    sorted->_size = vec._size;
    sorted->_capacity = vec._capacity;
    sorted->_strategy = vec._strategy;
    if (sorted->_strategy == ResizeStrategy::Additive)
        _coef = vec._coef;
    if (sorted->_strategy == ResizeStrategy::Multiplicative)
        _coef = vec._coef;
    sorted->_data = new ValueType[sorted->_capacity];
    if (strategy == SortedStrategy::Increase)
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
    else
    {
        size_t idx1 = 0;
        size_t idx2 = vec._size - 1;

        for (size_t i = 0; i < vec._size ; i++)
        {

            if (idx1 == idx2)
            {
                sorted->_data[i] = (vec._data[idx2])*(vec._data[idx2]);
            }

            if (idx1 != idx2)
            {

                if (abs(vec._data[idx1]) >= abs(vec._data[idx2]))
                {
                    sorted->_data[i] = vec._data[idx1]*vec._data[idx1];
                    idx1++;
                }
                else /*if (abs(vec._data[idx1]) < abs(vec._data[idx2]))*/
                {
                    sorted->_data[i] = (vec._data[idx2])*(vec._data[idx2]);
                    idx2--;
                }
            }
        }
    }
    return  *sorted;
}
