#pragma once
#include "StackImplementation.h"
#include "MyVector.h"

template <typename ValueType>
class VectorStack : public StackImplementation<ValueType>, public MyVector<ValueType>
{
public:
    VectorStack() {}
    VectorStack(const VectorStack& copyVector);
    void push(const ValueType &value) override;
    void pop() override;
    ValueType & top() override;
    const ValueType & top() const override;
    bool isEmpty() const override;
    size_t size() const override;

    ~VectorStack() override {};
};

template <typename ValueType>
VectorStack<ValueType>::VectorStack(const VectorStack &copy) : MyVector<ValueType>(copy)
{}

template <typename ValueType>
void VectorStack<ValueType>::push(const ValueType &value)
{
    this->pushBack(value);
}

template <typename ValueType>
void VectorStack<ValueType>::pop()
{
    if (isEmpty())
        throw std::out_of_range("stack is empty");
    this->popBack();
}

template <typename ValueType>
ValueType& VectorStack<ValueType>::top()
{
    return (*this)[size()-1];
}

template <typename ValueType>
const ValueType& VectorStack<ValueType>::top() const
{
    return (*this)[size()-1];
}

template <typename ValueType>
bool VectorStack<ValueType>::isEmpty() const
{
    if (size() == 0)
        return true;
    else
        return false;
}

template <typename ValueType>
size_t VectorStack<ValueType>::size() const
{
    return this->MyVector<ValueType>::size();
}
