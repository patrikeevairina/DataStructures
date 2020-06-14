#include "MyVector.h"


MyVector::MyVector(size_t size, ResizeStrategy ResizeStrategy, float coef)
{
    _size = size;
    _strategy = ResizeStrategy;
    _capacity = (_strategy == ResizeStrategy::Multiplicative) ? (size * coef) : (size + coef);
    _capacity = (_capacity == 0) ? 1 : _capacity;
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = ValueType();
        //std::cout << _data[i] << " " << std::endl;
    }
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
        //std::cout << _data[i] << " " << std::endl;
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
    std::swap(_data, bufVector._data);
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
    if (i >= _size)
        throw std::out_of_range("error");
    ValueType &res = _data[i];
    return res;
}


const ValueType& MyVector::operator[](const size_t i) const
{
    if (i >= _size)
        throw std::out_of_range("error");
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
            reserve(_capacity * _coef * _coef);
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
        throw std::out_of_range("error");
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
        throw std::out_of_range("error");
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


void MyVector::popBack()

{
    if (this->_data == nullptr)
        throw std::invalid_argument("inv arg");

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
    if (capacity() == 0)
        reserve(1);
    return;
}


void MyVector::erase(const size_t i, const size_t len)
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
        for (size_t i = size(); i >= 0; i--)
        {
            if (this->_data[i-1] == value)
                return i;
        }
    }
    return -1;
}


void MyVector::resize(const size_t size, const ValueType value)
{
    if (size > _capacity)
    {
        //std::cout << "newCap " << size*_coef << std::endl;
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
    _capacity = 0;
}

//template <typename ValueType>
//ValueType* MyVector<ValueType>::begin()
//{
//    return this->_data;
//}

//template <typename ValueType>
//ValueType* MyVector<ValueType>::end() const
//{
//    return this->_data+size();
//}


MyVector MyVector::sortedSquares(SortedStrategy strategy) // norm
{
    MyVector sorted = *this;
    // if (strategy == SortedStrategy::Increase)
    //{
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
    // }
    // else
    // {
    //   size_t idx1 = 0;
    //  size_t idx2 = this->_size - 1;

    //        for (size_t i = 0; i < this->_size ; i++)
    //        {

    //            if (idx1 == idx2)
    //            {
    //                sorted._data[i] = (this->_data[idx2])*(this->_data[idx2]);
    //            }

    //            if (idx1 != idx2)
    //            {

    //                if (abs(this->_data[idx1]) >= abs(this->_data[idx2]))
    //                {
    //                    sorted._data[i] = this->_data[idx1]*this->_data[idx1];
    //                    idx1++;
    //                }
    //                else /*if (abs(vec._data[idx1]) < abs(vec._data[idx2]))*/
    //                {
    //                    sorted._data[i] = (this->_data[idx2])*(this->_data[idx2]);
    //                    idx2--;
    //                }
    //            }
    //        }
    // }
    return  sorted;
}



