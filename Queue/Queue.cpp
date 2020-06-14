#include "Queue.h"


Queue::Queue(QueueContainer container)
    : _containerType(container)
{
    //    if (1 == 1)
    //        throw std::out_of_range("OMG");
    switch (container)
    {
    case QueueContainer::SinglyLinkedList: {
        _pimpl = new SingleListQueue();
        break;
    }
    case QueueContainer::Vector: {
        _pimpl = new VectorQueue();
        break;
    }
    case QueueContainer::DoublyLinkedList: {
        _pimpl = new DoubleListQueue();
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера!");
    }
}

Queue::Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container)
    : _containerType(container)
{
    switch (container)
    {
    case QueueContainer::SinglyLinkedList: {
        _pimpl = new SingleListQueue();
        break;
    }
    case QueueContainer::Vector: {
        _pimpl = new VectorQueue();
        break;
    }
    case QueueContainer::DoublyLinkedList: {
        _pimpl = new DoubleListQueue();
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
    for (size_t i = 0; i < arraySize; i++)
    {
        _pimpl->enqueue(valueArray[i]);
    }
}


Queue::Queue(const Queue& copyQueue)
{
    _containerType = copyQueue._containerType;
    switch (_containerType)
    {
    case QueueContainer::SinglyLinkedList: {
        _pimpl = new SingleListQueue(*(static_cast<SingleListQueue*>(copyQueue._pimpl)));
        break;
    }
    case QueueContainer::Vector: {
        _pimpl = new VectorQueue(*(static_cast<VectorQueue*>(copyQueue._pimpl)));
        break;
    }
    case QueueContainer::DoublyLinkedList: {
        _pimpl = new DoubleListQueue(*(static_cast<DoubleListQueue*>(copyQueue._pimpl)));
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
}


Queue& Queue::operator=(const Queue& copyQueue)
{
    if (this == &copyQueue)
        return *this;
    _containerType = copyQueue._containerType;
    delete _pimpl;
    switch (_containerType)
    {
    case QueueContainer::SinglyLinkedList: {
        _pimpl = new SingleListQueue(*(static_cast<SingleListQueue*>(copyQueue._pimpl)));	// конкретизируйте под ваши конструкторы, если надо
        break;
    }
    case QueueContainer::Vector: {
        _pimpl = new VectorQueue(*(static_cast<VectorQueue*>(copyQueue._pimpl)));	// конкретизируйте под ваши конструкторы, если надо
        break;
    }
    case QueueContainer::DoublyLinkedList: {
        _pimpl = new DoubleListQueue(*(static_cast<DoubleListQueue*>(copyQueue._pimpl)));
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
    return *this;
}


Queue::~Queue()
{
//    if (1 == 1)
//        throw std::out_of_range("OMG");
    delete _pimpl;		// композиция!
}

void Queue::enqueue(const ValueType& value)
{
    _pimpl->enqueue(value);
}


void Queue::dequeue()
{
    _pimpl->dequeue();
}

ValueType& Queue::front()
{
    return _pimpl->front();
}

const ValueType& Queue::front() const
{
    return _pimpl->front();
}


bool Queue::isEmpty()
{
    return _pimpl->isEmpty();
}


size_t Queue::size()
{
    return _pimpl->size();
}




