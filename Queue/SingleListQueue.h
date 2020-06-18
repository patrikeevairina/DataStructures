#pragma once

#include "QueueImplementation.h"
#include "LinkedList.h"

template <typename ValueType>
class SingleListQueue : public QueueImplementation<ValueType>, public LinkedList<ValueType>
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

template <typename ValueType>
SingleListQueue<ValueType>::SingleListQueue(const SingleListQueue& copy)
    :LinkedList<ValueType> (copy){}

template <typename ValueType>
void SingleListQueue<ValueType>::enqueue(const ValueType& value)
{
    this->pushBack(value);
}

template <typename ValueType>
void SingleListQueue<ValueType>::dequeue()
{
    if (this->isEmpty())
        throw std::out_of_range("incorrect");
    this->LinkedList<ValueType>::removeFront();
}

template <typename ValueType>
ValueType& SingleListQueue<ValueType>::front()
{
    return (*this)[0];
}

template <typename ValueType>
const ValueType& SingleListQueue<ValueType>::front() const
{
    return (*this)[0];
}

template <typename ValueType>
bool SingleListQueue<ValueType>::isEmpty() const
{
    if (size() == 0)
        return true;
    else
        return false;
}

template <typename ValueType>
size_t SingleListQueue<ValueType>::size() const
{
    return this->LinkedList<ValueType>::size();
}

