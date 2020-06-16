#pragma once

#include "StackImplementation.h"
#include "LinkedList.h"

class ListStack : public StackImplementation, public LinkedList
{
public:
    ListStack() {};
    ListStack(const ListStack &copyList);
    void push(const ValueType &value) override;
    void pop() override;
    ValueType& top() override;
    const ValueType & top() const override;
    bool isEmpty() const override;
    size_t size() const override;

    ~ListStack() override {};
};


