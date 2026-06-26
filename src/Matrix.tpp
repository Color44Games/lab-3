#pragma once

#include "../sequence/Exceptions.hpp"
#include "../sequence/MutableArraySequence.hpp"
#include "Matrix.hpp"


// Конструкторы RectangularMatrix
template <class T>
void RectangularMatrix<T>::check_row_index(int row_index) const {
    if (row_index >= this->rows || row_index < 0) {
        throw IndexOutOfRange("Matrix error: rows index out of range");
    }
}

template <class T>
void RectangularMatrix<T>::check_col_index(int col_index) const {
    if (col_index >= this->cols || col_index < 0) {
        throw IndexOutOfRange("Matrix error: cols index out of range");
    }
}

template <class T>
RectangularMatrix<T>::RectangularMatrix() : storage(), rows(0), cols(0) {}

template <class T>
RectangularMatrix<T>::RectangularMatrix(int rows, int cols) : rows(rows), cols(cols) {
    if (rows < 0 || cols < 0) {
        throw IndexOutOfRange("Matrix error: negative initialize sizes given");
    }

    typename MutableArraySequence<MutableArraySequence<T>>::Builder resultBuilder;

    for (int i = 0; i < rows; i++) {
        typename MutableArraySequence<T>::Builder rowBuilder;

        for (int j = 0; j < cols; j++) {
            rowBuilder.Append(T());
        }

        MutableArraySequence<T>* createdRow = rowBuilder.Build();
        resultBuilder.Append(*createdRow);
        delete createdRow;
    }

    MutableArraySequence<MutableArraySequence<T>>* createdMatrix = resultBuilder.Build();
    this->storage = *createdMatrix;
    delete createdMatrix;
}

template <class T>
RectangularMatrix<T>::RectangularMatrix(const RectangularMatrix& other)
    : storage(other.storage), rows(other.rows), cols(other.cols) {}

template <class T>
RectangularMatrix<T>::RectangularMatrix(RectangularMatrix&& other) noexcept
    : storage(std::move(other.storage)), rows(other.rows), cols(other.cols) {
    other.rows = 0;
    other.cols = 0;
}

// Геттеры RectangularMatrix
template <class T>
int RectangularMatrix<T>::GetRows() const {
    return this->rows;
}

template <class T>
int RectangularMatrix<T>::GetCols() const {
    return this->cols;
}

template <class T>
T& RectangularMatrix<T>::Get(int row_ind, int col_ind) {
    check_row_index(row_ind);
    check_col_index(col_ind);

    return storage[row_ind][col_ind];
}

template <class T>
const T& RectangularMatrix<T>::Get(int row_ind, int col_ind) const {
    check_row_index(row_ind);
    check_col_index(col_ind);

    return storage[row_ind][col_ind];
}

// Операции RectangularMatrix
template <class T>
void RectangularMatrix<T>::SwapRows(int r1_ind, int r2_ind) {
    check_row_index(r1_ind);
    check_row_index(r2_ind);

    if (r1_ind == r2_ind) {
        return;
    }

    std::swap(storage[r1_ind], storage[r2_ind]);
}

template <class T>
void RectangularMatrix<T>::MultiplyRow(int row_ind, T multiplicator) {
    check_row_index(row_ind);

    for (int j = 0; j < this->cols; j++) {
        storage[row_ind][j] *= multiplicator;
    }
}

template <class T>
void RectangularMatrix<T>::IncreaseRow(int row_ind, T value) {
    check_row_index(row_ind);

    for (int j = 0; j < this->cols; j++) {
        storage[row_ind][j] += value;
    }
}

template <class T>
void RectangularMatrix<T>::SwapCols(int c1_ind, int c2_ind) {
    check_col_index(c1_ind);
    check_col_index(c2_ind);

    if (c1_ind == c2_ind) {
        return;
    }

    for (int i = 0; i < this->rows; i++) {
        std::swap(storage[i][c1_ind], storage[i][c2_ind]);
    }
}

template <class T>
void RectangularMatrix<T>::MultiplyCol(int col_ind, T multiplicator) {
    check_col_index(col_ind);

    for (int i = 0; i < this->rows; i++) {
        storage[i][col_ind] *= multiplicator;
    }
}

template <class T>
void RectangularMatrix<T>::IncreaseCol(int col_ind, T value) {
    check_col_index(col_ind);

    for (int i = 0; i < this->rows; i++) {
        storage[i][col_ind] += value;
    }
}

template <class T>
double RectangularMatrix<T>::norm() const {
    double result = 0.0;

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            double value = static_cast<double>(storage[i][j]);  // Необходимо, чтобы тип T был приводимым к double
            result += value * value;
        }
    }

    return std::sqrt(result);
}

// Операторы RectangularMatrix
template <class T>
RectangularMatrix<T>& RectangularMatrix<T>::operator=(const RectangularMatrix<T>& other) {
    if (this != &other) {
        this->rows = other.rows;
        this->cols = other.cols;
        this->storage = other.storage;
    }

    return *this;
}

template <class T>
RectangularMatrix<T>& RectangularMatrix<T>::operator=(RectangularMatrix<T>&& other) noexcept {
    if (this != &other) {
        this->storage = std::move(other.storage);
        this->rows = other.rows;
        this->cols = other.cols;
        other.rows = 0;
        other.cols = 0;
    }

    return *this;
}

template <class T>
T& RectangularMatrix<T>::operator()(int row_index, int col_index) {
    return Get(row_index, col_index);
}

template <class T>
const T& RectangularMatrix<T>::operator()(int row_index, int col_index) const {
    return Get(row_index, col_index);
}

template <class T>
RectangularMatrix<T> RectangularMatrix<T>::operator+(const RectangularMatrix<T>& other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw RunTimeError("Matrix addition error: different size of given matrix");
    }

    RectangularMatrix<T> result(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }

    return result;
}

template <class T>
RectangularMatrix<T> RectangularMatrix<T>::operator*(const RectangularMatrix<T>& other) const {
    if (this->cols != other.rows) {
        throw RunTimeError("Matrix multiplication error: invalid sizes");
    }

    RectangularMatrix<T> result(this->rows, other.cols);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            T line_sum = T();

            for (int k = 0; k < this->cols; k++) {
                line_sum += (*this)(i, k) * other(k, j);
            }

            result(i, j) = line_sum;
        }
    }

    return result;
}

template <class T>
RectangularMatrix<T> RectangularMatrix<T>::operator*(T multiplicator) const {
    RectangularMatrix<T> result(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result(i, j) = (*this)(i, j) * multiplicator;
        }
    }

    return result;
}

// Конструкторы SquareMatrix
template <class T>
void SquareMatrix<T>::check_same_size(const SquareMatrix<T>& other) const {
    if (this->GetSize() != other.GetSize()) {
        throw RunTimeError("Matrix error: different size of given matrix");
    }
}

template <class T>
SquareMatrix<T>::SquareMatrix() : RectangularMatrix<T>() {}

template <class T>
SquareMatrix<T>::SquareMatrix(int size) : RectangularMatrix<T>(size, size) {}

template <class T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T>& other) : RectangularMatrix<T>(other) {}

template <class T>
SquareMatrix<T>::SquareMatrix(SquareMatrix<T>&& other) noexcept : RectangularMatrix<T>(std::move(other)) {}

// Геттеры SquareMatrix
template <class T>
int SquareMatrix<T>::GetSize() const {
    return this->GetRows();
}

// Операторы SquareMatrix
template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const SquareMatrix<T>& other) {
    if (this != &other) {
        RectangularMatrix<T>::operator=(other);
    }

    return *this;
}

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator=(SquareMatrix<T>&& other) noexcept {
    if (this != &other) {
        RectangularMatrix<T>::operator=(std::move(other));
    }

    return *this;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix<T>& other) const {
    check_same_size(other);

    SquareMatrix<T> result(this->GetSize());

    for (int i = 0; i < this->GetSize(); i++) {
        for (int j = 0; j < this->GetSize(); j++) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }

    return result;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::operator*(const SquareMatrix<T>& other) const {
    check_same_size(other);

    SquareMatrix<T> result(this->GetSize());

    for (int i = 0; i < this->GetSize(); i++) {
        for (int j = 0; j < this->GetSize(); j++) {
            T line_sum = T();

            for (int k = 0; k < this->GetSize(); k++) {
                line_sum += (*this)(i, k) * other(k, j);
            }

            result(i, j) = line_sum;
        }
    }

    return result;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::operator*(T multiplicator) const {
    SquareMatrix<T> result(this->GetSize());

    for (int i = 0; i < this->GetSize(); i++) {
        for (int j = 0; j < this->GetSize(); j++) {
            result(i, j) = (*this)(i, j) * multiplicator;
        }
    }

    return result;
}