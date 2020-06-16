#include "VectorStack.h"

VectorStack::VectorStack(const VectorStack &copy) : MyVector(copy)
{}

void VectorStack::push(const ValueType &value)
{
    this->pushBack(value);
}

void VectorStack::pop()
{
    if (isEmpty())
        throw std::out_of_range("stack is empty");
    this->popBack();
}

ValueType& VectorStack::top()
{
    return (*this)[size()-1];
}#pragma once
#include "StackImplementation.h"
#include "MyVector.h"

class VectorStack : public StackImplementation, public MyVector
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



const ValueType& VectorStack::top() const
{
    return (*this)[size()-1];
}

bool VectorStack::isEmpty() const
{
    if (size() == 0)
        return true;
    else
        return false;
}

size_t VectorStack::size() const
{
    return this->MyVector::size();
}
