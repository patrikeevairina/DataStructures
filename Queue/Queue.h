
#include <iostream>
#include <cstring>
#include "SingleListQueue.h"
#include "VectorQueue.h"
#include "DoubleListQueue.h"
#include "QueueImplementation.h"

#pragma once
//#define ValueType double

enum class QueueContainer
{
    Vector = 0,
    SinglyLinkedList,
    DoublyLinkedList,
};

class QueueImplementation;


class Queue
{
public:
    Queue(QueueContainer container = QueueContainer::DoublyLinkedList);
    Queue(const ValueType *valueArray, const size_t arraySize,
          QueueContainer container = QueueContainer::DoublyLinkedList);
    explicit Queue(const Queue& copyQueue);
    Queue& operator=(const Queue& copyQueue);

    ~Queue();

    void enqueue(const ValueType& value);
    void dequeue();
    ValueType& front();
    const ValueType& front() const;
    bool isEmpty();
    size_t size();

private:
    QueueImplementation* _pimpl = nullptr;
    QueueContainer _containerType;
};

