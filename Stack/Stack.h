#include <iostream>
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"

#pragma once

enum class StackContainer {
    Vector = 0,
    List,
};

class Stack
{
public:
    Stack(StackContainer container = StackContainer::List);
    Stack(const ValueType* valueArray, const size_t arraySize,
          StackContainer container = StackContainer::List);
    explicit Stack(const Stack& copyStack);
    Stack& operator=(const Stack& copyStack);
    Stack(Stack&& moveStack) noexcept;
    Stack& operator=(Stack&& moveStack) noexcept;
    ~Stack();
    
    void push(const ValueType& value);
    void pop();
    ValueType& top();
    const ValueType& top() const;
    bool isEmpty() const;
    size_t size() const;
private:
    StackImplementation* _pimpl = nullptr;
    StackContainer _containerType;
};

