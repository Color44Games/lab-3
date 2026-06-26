#pragma once

#include "Queue.hpp"

// Конструкторы
template <class T>
Queue<T>::Queue(T* items, int size) : storage(items, size) {}

template <class T>
Queue<T>::Queue(const Queue<T>& other) : storage(other.storage) {}

template <class T>
Queue<T>::Queue(Queue<T>&& other) noexcept : storage(std::move(other.storage)) {}

// Геттеры и операции
template <class T>
int Queue<T>::GetLength() const {
    return this->storage.GetLength();
}

template <class T>
IEnumerator<T>* Queue<T>::GetEnumerator() const {
    return this->storage.GetEnumerator();
}

template <class T>
void Queue<T>::Enqueue(const T& value) {
    this->storage.Append(value);
}

template <class T>
T Queue<T>::Dequeue() {
    if (IsEmpty()) {
        throw EmptyCollectionError("Deque error: empty collection is given");
    }

    return this->storage.RemoveAt(0);
}

template <class T>
bool Queue<T>::IsEmpty() const {
    return (this->storage.GetLength() == 0);
}

template <class T>
const T& Queue<T>::Peek() const {
    if (IsEmpty()) {
        throw EmptyCollectionError("Peek error: empty collection is given");
    }

    return this->storage.GetFirst();
}

// Map, where, reduce
template <class T>
Queue<T> Queue<T>::Map(T (*func)(T)) const {
    Queue<T> result;

    for (int i = 0; i < this->storage.GetLength(); i++) {
        result.Enqueue(func(this->storage.Get(i)));
    }

    return result;
}

template <class T>
Queue<T> Queue<T>::Where(bool (*predicate)(T)) const {
    Queue<T> result;

    for (int i = 0; i < this->storage.GetLength(); i++) {
        if (predicate(this->storage.Get(i))) {
            result.Enqueue(this->storage.Get(i));
        }
    }

    return result;
}

template <class T>
T Queue<T>::Reduce(T (*func)(T, T), const T& initial) const {
    T accum = initial;

    for (int i = 0; i < this->storage.GetLength(); i++) {
        accum = func(this->storage.Get(i), accum);
    }

    return accum;
}

// Дополнительные операции
template <class T>
Queue<T> Queue<T>::Concat(const Queue<T>& other) const {
    Queue<T> result(*this);

    for (int i = 0; i < other.GetLength(); i++) {
        result.Enqueue(other.storage.Get(i));
    }

    return result;
}

template <class T>
Queue<T> Queue<T>::GetSubsequence(int start_index, int end_index) const {
    Queue<T> result;

    if (start_index < 0 || end_index > this->GetLength() || start_index > end_index) {
        throw IndexOutOfRange("GetSubsequence error: invalid indexes range");
    }

    for (int i = start_index; i < end_index; i++) {
        result.Enqueue(this->storage.Get(i));
    }

    return result;
}

template <class T>
int Queue<T>::FindSubsequence(const Queue<T>& sub) const {
    int que_size = this->GetLength();
    int sub_size = sub.GetLength();

    if (sub_size > que_size) {
        return -1;
    }

    if (sub_size == 0) {
        return 0;
    }

    for (int i = 0; i <= que_size - sub_size; i++) {
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
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        this->storage = other.storage;
    }

    return *this;
}

template <class T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept {
    if (this != &other) {
        this->storage = std::move(other.storage);
    }

    return *this;
}

template <class T>
bool Queue<T>::operator==(const Queue<T>& other) const {
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
bool Queue<T>::operator!=(const Queue<T>& other) const {
    return !(*this == other);
}
