#pragma once

#include "QueueImplementation.h"
#include "LinkedList.h"


class SingleListQueue : public QueueImplementation, public LinkedList
{
public:
    SingleListQueue(){}
    SingleListQueue(const SingleListQueue& copyList);
    void enqueue(const ValueType& value) override;
    void dequeue() override;
    ValueType& front() override;
    const ValueType& front() const override;
    bool isEmpty() const override;
    size_t size() const override;
    ~SingleListQueue() override {};
};


