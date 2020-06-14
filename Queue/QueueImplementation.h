#pragma once

#include <iostream>
#define ValueType double


class QueueImplementation
{
public:
    virtual void enqueue(const ValueType &value) = 0;
    virtual void dequeue() = 0;
    virtual ValueType& front() = 0;
    virtual const ValueType& front() const = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t size() const = 0;
    virtual ~QueueImplementation() {};
};
