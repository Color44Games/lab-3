#pragma once

#include "../sequence/IEnumerable.hpp"
#include "../sequence/LinkedList.hpp"

template <class T>
class Queue : public IEnumerable<T> {
private:
    LinkedList<T> storage;

public:
    // Конструкторы
    Queue() = default;
    Queue(T* items, int size);
    Queue(const Queue<T>& other);
    Queue(Queue<T>&& other) noexcept;
    ~Queue() override = default;

    // Геттеры и операции
    int GetLength() const;
    IEnumerator<T>* GetEnumerator() const override;
    void Enqueue(const T& value);
    T Dequeue();
    bool IsEmpty() const;
    const T& Peek() const;

    // Map, where, reduce
    Queue<T> Map(T (*func)(T)) const;
    Queue<T> Where(bool (*predicate)(T)) const;
    T Reduce(T (*func)(T, T), const T& initial) const;

    // Дополнительные операции
    Queue<T> Concat(const Queue<T>& other) const;
    Queue<T> GetSubsequence(int start_index, int end_index) const;
    int FindSubsequence(const Queue<T>& sub) const;

    // Операторы
    Queue<T>& operator=(const Queue<T>& other);
    Queue<T>& operator=(Queue<T>&& other) noexcept;
    bool operator==(const Queue<T>& other) const;
    bool operator!=(const Queue<T>& other) const;
};

#include "Queue.tpp"