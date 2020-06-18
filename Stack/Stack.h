#include <iostream>
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"

#pragma once

enum class StackContainer {
    Vector = 0,
    List,
};

template <typename ValueType>
class Stack
{
public:
    Stack(StackContainer container = StackContainer::List);
    Stack(const ValueType* valueArray, const size_t arraySize,
          StackContainer container = StackContainer::List);
    explicit Stack(const Stack& copyStack);
    Stack& operator=(const Stack& copyStack);
    Stack(Stack&& moveStack) noexcept;
    Stack& operator=(Stack&& moveStack) noexcept;
    ~Stack();
    
    void push(const ValueType& value);
    void pop();
    ValueType& top();
    const ValueType& top() const;
    bool isEmpty() const;
    size_t size() const;
private:
    StackImplementation<ValueType>* _pimpl = nullptr;
    StackContainer _containerType;
};

template <typename ValueType>
Stack<ValueType>::Stack(StackContainer container)
    : _containerType(container)
{
    switch (container)
    {
    case StackContainer::List: {
        _pimpl = new ListStack<ValueType>();
        break;
    }
    case StackContainer::Vector: {
        _pimpl = new VectorStack<ValueType>();
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
}

template <typename ValueType>
Stack<ValueType>::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
    : _containerType(container)
{
    switch (container)
    {
    case StackContainer::List: {
        _pimpl = new ListStack<ValueType>();
        break;
    }
    case StackContainer::Vector: {
        _pimpl = new VectorStack<ValueType>();
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
    for (size_t i = 0; i < arraySize; i++)
    {
        this->push(valueArray[i]);
    }
}

template <typename ValueType>
Stack<ValueType>::Stack(const Stack& copyStack)
{
    _containerType = copyStack._containerType;
    switch (_containerType)
    {
    case StackContainer::List: {
        _pimpl = new ListStack<ValueType>(*(static_cast<ListStack<ValueType>*>(copyStack._pimpl)));
        break;
    }
    case StackContainer::Vector: {
        _pimpl = new VectorStack<ValueType>(*(static_cast<VectorStack<ValueType>*>(copyStack._pimpl)));
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
}

template <typename ValueType>
Stack<ValueType>& Stack<ValueType>::operator=(const Stack& copyStack)
{
    if (this == &copyStack)
        return *this;
    _containerType = copyStack._containerType;
    delete _pimpl;
    switch (_containerType)
    {
    case StackContainer::List: {
        _pimpl = new ListStack<ValueType>(*(static_cast<ListStack<ValueType>*>(copyStack._pimpl)));
        break;
    }
    case StackContainer::Vector: {
        _pimpl = new VectorStack<ValueType>(*(static_cast<VectorStack<ValueType>*>(copyStack._pimpl)));
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
    return *this;
}

template <typename ValueType>
Stack<ValueType>::Stack(Stack&& moveStack) noexcept
{
    _containerType = moveStack._containerType;
    delete _pimpl;
    _pimpl = moveStack._pimpl;
    moveStack._pimpl = nullptr;
}

template <typename ValueType>
Stack<ValueType>& Stack<ValueType>::operator=(Stack &&moveStack) noexcept
{
    if (this == &moveStack)
    {
        return *this;
    }
    delete _pimpl;
    _containerType = moveStack._containerType;
    _pimpl = moveStack._pimpl;
    
    moveStack._pimpl = nullptr;
    
    return *this;
}

template <typename ValueType>
Stack<ValueType>::~Stack()
{
    delete _pimpl;
}

template <typename ValueType>
void Stack<ValueType>::push(const ValueType& value)
{
    _pimpl->push(value);
}

template <typename ValueType>
void Stack<ValueType>::pop()
{
    _pimpl->pop();
}

template <typename ValueType>
ValueType& Stack<ValueType>::top()
{
    return _pimpl->top();
}

template <typename ValueType>
const ValueType& Stack<ValueType>::top() const
{
    return _pimpl->top();
}

template <typename ValueType>
bool Stack<ValueType>::isEmpty() const
{
    return _pimpl->isEmpty();
}

template <typename ValueType>
size_t Stack<ValueType>::size() const
{
    return _pimpl->size();
}
