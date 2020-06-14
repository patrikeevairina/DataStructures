#include "VectorQueue.h"

VectorQueue::VectorQueue(const VectorQueue& copy)
    :MyVector (copy){}


void VectorQueue::enqueue(const ValueType& value)
{
    this->MyVector::pushBack(value);
}

void VectorQueue::dequeue()
{
    if (this->isEmpty())
        throw std::out_of_range("incorrect");
    this->MyVector::erase(0);
    //std::cout << (*this)[0] << std::endl;
}


ValueType& VectorQueue::front()
{
    return (*this)[0];
}


const ValueType& VectorQueue::front() const
{
    return (*this)[0];
}


bool VectorQueue::isEmpty() const
{
    if (size() == 0)
        return true;
    else
        return false;
}


size_t VectorQueue::size() const
{
    return this->MyVector::size();
}


