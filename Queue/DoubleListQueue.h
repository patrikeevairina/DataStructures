#pragma once

#include "QueueImplementation.h"
#include "DoubleLinkedList.h"

class DoubleListQueue : public QueueImplementation, public DoubleLinkedList
{
public:
    DoubleListQueue(){}
    DoubleListQueue(const DoubleListQueue& copyList);
    void enqueue(const ValueType& value) override;
    void dequeue() override;
    ValueType& front() override;
    const ValueType& front() const override;
    bool isEmpty() const override;
    size_t size() const override;
    ~DoubleListQueue() override = default;
};

