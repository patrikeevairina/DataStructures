#include "SingleListQueue.h"

SingleListQueue::SingleListQueue(const SingleListQueue& copy)
    :LinkedList (copy){}


void SingleListQueue::enqueue(const ValueType& value)
{
    this->pushBack(value);
}


void SingleListQueue::dequeue()
{
    if (this->isEmpty())
        throw std::out_of_range("incorrect");
    this->LinkedList::removeFront();
}


ValueType& SingleListQueue::front()
{
    return (*this)[0];
}


const ValueType& SingleListQueue::front() const
{
    return (*this)[0];
}

bool SingleListQueue::isEmpty() const
{
    if (size() == 0)
        return true;
    else
        return false;
}


size_t SingleListQueue::size() const
{
    return this->LinkedList::size();
}

