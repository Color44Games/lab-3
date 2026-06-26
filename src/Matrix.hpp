#pragma once

#include "../sequence/MutableArraySequence.hpp"

template <class T>
class RectangularMatrix {
protected:
    MutableArraySequence<MutableArraySequence<T>> storage;
    int rows;
    int cols;

    void check_row_index(int row_index) const;
    void check_col_index(int col_index) const;

public:
    // Конструкторы и деструктор
    RectangularMatrix();
    RectangularMatrix(int rows, int cols);
    RectangularMatrix(const RectangularMatrix<T>& other);
    RectangularMatrix(RectangularMatrix&& other) noexcept;
    virtual ~RectangularMatrix() = default;

    // Геттеры
    int GetRows() const;
    int GetCols() const;

    T& Get(int row_ind, int col_ind);
    const T& Get(int row_ind, int col_ind) const;

    // Операции
    void SwapRows(int r1_ind, int r2_ind);
    void MultiplyRow(int row_ind, T multiplicator);
    void IncreaseRow(int row_ind, T vaule);

    void SwapCols(int c1_ind, int c2_ind);
    void MultiplyCol(int col_ind, T multiplicator);
    void IncreaseCol(int col_ind, T vaule);

    double norm() const;

    // Операторы
    RectangularMatrix<T>& operator=(const RectangularMatrix<T>& other);
    RectangularMatrix<T>& operator=(RectangularMatrix<T>&& other) noexcept;

    T& operator()(int row_index, int col_index);
    const T& operator()(int row_index, int col_index) const;

    RectangularMatrix<T> operator+(const RectangularMatrix<T>& other) const;
    RectangularMatrix<T> operator*(const RectangularMatrix<T>& other) const;
    RectangularMatrix<T> operator*(T multiplicator) const;
};

template <class T>
class SquareMatrix : public RectangularMatrix<T> {
protected:
    void check_same_size(const SquareMatrix& other) const;

public:
    // Конструкторы и деструктор
    SquareMatrix();
    SquareMatrix(int size);
    SquareMatrix(const SquareMatrix<T>& other);
    SquareMatrix(SquareMatrix<T>&& other) noexcept;
    ~SquareMatrix() override = default;

    // Геттеры
    int GetSize() const;

    // Операторы
    SquareMatrix<T>& operator=(const SquareMatrix<T>& other);
    SquareMatrix<T>& operator=(SquareMatrix<T>&& other) noexcept;

    SquareMatrix<T> operator+(const SquareMatrix<T>& other) const;
    SquareMatrix<T> operator*(const SquareMatrix<T>& other) const;
    SquareMatrix<T> operator*(T multiplicator) const;
};

#include "Matrix.tpp"