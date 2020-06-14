#include "DoubleListQueue.h"


DoubleListQueue::DoubleListQueue(const DoubleListQueue& copy)
    :DoubleLinkedList(copy){}


void DoubleListQueue::enqueue(const ValueType& value)
{
    this->pushBack(value);
}


void DoubleListQueue::dequeue()
{
    if (this->isEmpty())
        throw std::out_of_range("incorrect");
    this->DoubleLinkedList::removeFront();
}

ValueType& DoubleListQueue::front()
{
    return (*this)[0];
}

const ValueType& DoubleListQueue::front() const
{
    return (*this)[0];
}

bool DoubleListQueue::isEmpty() const
{
    if (size() == 0)
        return true;
    else
        return false;
}


size_t DoubleListQueue::size() const
{
    return this->DoubleLinkedList::size();
}

