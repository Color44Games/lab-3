#pragma once

#include "Stack.hpp"

// Конструкторы
template <class T>
Stack<T>::Stack(T* items, int size) : storage(items, size) {}

template <class T>
Stack<T>::Stack(const Stack<T>& other) : storage(other.storage) {}

template <class T>
Stack<T>::Stack(Stack<T>&& other) noexcept : storage(std::move(other.storage)) {}

// Геттеры и операции
template <class T>
int Stack<T>::GetLength() const {
    return this->storage.GetLength();
}

template <class T>
IEnumerator<T>* Stack<T>::GetEnumerator() const {
    return this->storage.GetEnumerator();
}

template <class T>
void Stack<T>::Push(const T& item) {
    this->storage.Append(item);
}

template <class T>
T Stack<T>::Pop() {
    if (this->GetLength() == 0) {
        throw EmptyCollectionError("Pop error: empty collection is given");
    }

    return this->storage.RemoveAt(this->GetLength() - 1);
}

template <class T>
bool Stack<T>::IsEmpty() const {
    return (this->GetLength() == 0);
}

template <class T>
const T& Stack<T>::Peek() const {
    if (this->GetLength() == 0) {
        throw EmptyCollectionError("Pop error: empty collection is given");
    }

    return this->storage->GetLast();
}

//  Map, where, reduce
template <class T>
Stack<T> Stack<T>::Map(T (*func)(T)) const {
    Stack<T> result;

    for (int i, i < this->GetLength(); i++) {
        result.Push(func(this->storage->Get(i)));
    }

    return result;
}

template <class T>
Stack<T> Stack<T>::Where(bool (*predicate)(T)) const {
    Stack<T> result;

    for (int i = 0; i < this->GetLength(); i++) {
        if (predicate(this->storage.Get(i))) {
            result.Push(this->storage.Get(i));
        }
    }

    return result;
}

template <class T>
T Stack<T>::Reduce(T (*func)(T, T), const T& initial) const {
    T accum = initial;

    for (int i = 0; i < this->GetLength(); i++) {
        accum = func(this->storage.Get(i), accum);
    }

    return accum;
}

// Другие операции
template <class T>
Stack<T> Stack<T>::Concat(const Stack<T>& other) const {
    Stack<T> result(*this);

    for (int i = 0; i < other.GetLength(); i++) {
        result.Push(other.storage.Get(i));
    }

    return result;
}

template <class T>
Stack<T> Stack<T>::GetSubsequence(int start_index, int end_index) const {
    if (start_index < 0 || end_index > this->GetLength() || start_index > end_index) {
        throw IndexOutOfRange("GetSubsequence error: invalid indexes range");
    }

    Stack<T> result;

    for (int i = start_index; i < end_index; i++) {
        result.Push(this->storage.Get(i));
    }

    return result;
}

template <class T>
int Stack<T>::FindSubsequence(const Stack<T>& sub) const {
    int stack_size = this->GetLength();
    int sub_size = sub.GetLength();

    if (sub_size > stack_size) {
        return -1;
    }

    if (sub_size == 0) {
        return 0;
    }

    for (int i = 0; i <= stack_size - sub_size; i++) {
        bool is_same = true;
        for (int j = 0; j < sub_size; j++) {
            if (this->storage.Get(i + j) != sub.storage.Get(j)) {
                is_same = false;
                break;
            }
        }

        if (is_same) {
            return i;
        }
    }

    return -1;
}

// Операторы
template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
        this->storage = other.storage;
    }

    return *this;
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept {
    if (this != &other) {
        this->storage = std::move(other.storage);
    }

    return *this;
}

template <class T>
bool Stack<T>::operator==(const Stack<T>& other) const {
    if (this->GetLength() != other.GetLength()) {
        return false;
    }

    for (int i = 0; i < this->GetLength(); i++) {
        if (this->storage.Get(i) != other.storage.Get(i)) {
            return false;
        }
    }

    return true;
}

template <class T>
bool Stack<T>::operator!=(const Stack<T>& other) const {
    return !(*this == other);
}