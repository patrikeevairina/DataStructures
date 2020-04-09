#include "vector.h"

#include <iostream>
#include <cassert>
#include <cstring>

MyVector::MyVector(size_t size, ResizeStrategy, float coef)
{
    _size = size;
    _capacity = 1;
    _data = nullptr;
    _coef = coef;
    std::cout << "Creating 1" << std::endl;
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy, float coef)
{
//    std::cout << "1" << std::endl;
    _capacity = size * coef;
    _size = size;
    _data = new ValueType[_capacity];
//    std::cout << "2" << std::endl;
    for (size_t i = 0; i < _size; i++)
    {
//        std::cout << i << std::endl;
        _data[i] = value;
    }
    _coef = coef;
    std::cout << "Creating 2 " << std::endl;
}

MyVector::MyVector(const MyVector& copy)
{
//    std::cout << "1" << std::endl;
    _size = copy._size;
//    std::cout << "2" << std::endl;
    _capacity = copy._capacity;
//    std::cout << "3" << std::endl;
    _data = new ValueType[_capacity];
//    std::cout << "4" << std::endl;
    memcpy(_data, copy._data, sizeof(ValueType)*(_size));
    _coef = copy._coef;
    std::cout << "Creating 3" << std::endl;
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
    memcpy(this->_data, copy._data, this->_size * sizeof (ValueType));
    this->_coef = bufVector._coef;
    std::cout << "Worked operator = " << std::endl;
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
    std::cout << "Removing" << std::endl;
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
    return (float)(_size / _capacity);
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
    if (loadFactor() < 1)
        return;

    _capacity = (_capacity == 0) ? 1 : _capacity;
    while(_capacity < capacity)
        _capacity <<= 1;

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
        reserve(_capacity * _coef);
    }
    ValueType *copy = new ValueType[_size + 1];
    memcpy(copy, this->_data, _size * sizeof(ValueType));
    copy[_size] = value;
    if (this->_data != nullptr)
        delete[] this->_data;
    this->_data = copy;
    _size++;
    return;
}

void MyVector::insert(const size_t i, const ValueType &value)
{
    if (i > _size)
        return;

    if (loadFactor() == 1)
        reserve(_size * _coef);

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

    return;
}

void MyVector::insert(const size_t i, const MyVector &value)
{
    if (i > _size)
        return;
    _size += value._size;
    if (loadFactor() > 1)
        reserve(_size * _coef);
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
            _size = oldSize;
            reserve(size * _coef);
            _size = size;
        }
        for (size_t i = oldSize; i < _size; i++)
        {
            this->_data[i] = value;
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
    }
}

void MyVector::clear()
{
    delete[] _data;
    _size = 0;
}
