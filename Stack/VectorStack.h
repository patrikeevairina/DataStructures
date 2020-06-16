#pragma once
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

