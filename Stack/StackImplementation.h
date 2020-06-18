#pragma once
#include <iostream>

//using ValueType = double;

template <typename ValueType>
class StackImplementation {
public:
    virtual void push(const ValueType& value) = 0;
    virtual void pop() = 0;
    virtual ValueType& top() = 0;
    virtual const ValueType& top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t size() const = 0;
    virtual ~StackImplementation() {};
};
