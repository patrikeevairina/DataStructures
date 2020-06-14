#pragma once

#include "QueueImplementation.h"
#include "MyVector.h"


class VectorQueue : public QueueImplementation, public MyVector
{
public:
    VectorQueue(){}
    VectorQueue(const VectorQueue& copyVector);
    void enqueue(const ValueType& value) override;
    void dequeue() override;
    ValueType& front() override;
    const ValueType& front() const override;
    bool isEmpty() const override;
    size_t size() const override;
    ~VectorQueue() override {};
};


