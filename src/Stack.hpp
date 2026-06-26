#pragma once

#include "../sequence/IEnumerable.hpp"
#include "../sequence/LinkedList.hpp"

template <class T>
class Stack : public IEnumerable<T> {
private:
    LinkedList<T> storage;

public:
    // Конструкторы и деструктор
    Stack() = default;
    Stack(T* items, int size);
    Stack(const Stack<T>& other);
    Stack(Stack<T>&& other) noexcept;
    ~Stack() override = default;

    // Геттеры и операции
    int GetLength() const;
    IEnumerator<T>* GetEnumerator() const override;
    void Push(const T& value);
    T Pop();
    bool IsEmpty() const;
    const T& Peek() const;

    // Map, where, reduce
    Stack<T> Map(T (*func)(T)) const;
    Stack<T> Where(bool (*predicate)(T)) const;
    T Reduce(T (*func)(T, T), const T& initial) const;

    // Дополнительные операции
    Stack<T> Concat(const Stack<T>& other) const;
    Stack<T> GetSubsequence(int start_index, int end_index) const;
    int FindSubsequence(const Stack<T>& sub) const;

    // Операторы
    Stack<T>& operator=(const Stack<T>& other);
    Stack<T>& operator=(Stack<T>&& other) noexcept;
    bool operator==(const Stack<T>& other) const;
    bool operator!=(const Stack<T>& other) const;
};

#include "Stack.tpp"