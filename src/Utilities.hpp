#pragma once

#include <iostream>
#include <limits>
#include <string>

#include "Complex.hpp"
#include "Function.hpp"
#include "Matrix.hpp"
#include "Person.hpp"
#include "Queue.hpp"
#include "Stack.hpp"


// Вывод
inline std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.re << (c.im >= 0 ? "+" : "-") << c.im << "i";

    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Function& f) {
    return os << f.GetFuncName() << "()";
}

inline std::ostream& operator<<(std::ostream& os, const Student& st) {
    return os << "Студент: " << st.GetFullName() << " " << "Группа: " << st.GetGroupNumber() << " "
              << "Год поступления: " << st.GetAdmisionYear() << " " << "Средняя оценка: " << st.GetAverageGrade();
}

inline std::ostream& operator<<(std::ostream& os, const Teacher& te) {
    return os << "Преподаватель: " << te.GetFullName() << " " << "Предмет: " << te.GetSubjectName() << " "
              << "Факультет: " << te.GetFacultyName();
}

template <class T>
void PrintQueue(const Queue<T>& queue) {
    if (queue.IsEmpty()) {
        std::cout << "Очередь пуста!\n";
        return;
    }

    std::cout << "Очередь (начало -> конец): [";

    IEnumerator<T>* en = queue.GetEnumerator();
    bool first = true;

    while (en->MoveNext()) {
        if (!first) {
            std::cout << ", ";
        }

        std::cout << en->GetCurrent();
        first = false;
    }

    std::cout << "]\n";
    delete en;
}

template <class T>
void PrintStack(const Stack<T>& stack) {
    if (stack.IsEmpty()) {
        std::cout << "Стэк пуст!\n";
        return;
    }

    std::cout << "Стэк (низ -> вершина): [";

    IEnumerator<T>* en = stack.GetEnumerator();
    bool first = true;

    while (en->MoveNext()) {
        if (!first) {
            std::cout << ", ";
        }

        std::cout << en->GetCurrent();
        first = false;
    }
    std::cout << "]\n";
    delete en;
}

template <class T>
void PrintMatrix(const RectangularMatrix<T>& matrix) {
    std::cout << "Матрица (" << matrix.GetRows() << "x" << matrix.GetCols() << "):\n";
    for (int i = 0; i < matrix.GetRows(); i++) {
        for (int j = 0; j < matrix.GetCols(); j++) {
            std::cout << matrix(i, j) << " ";
        }
        std::cout << "\n";
    }
}

//  Ввод
inline int ReadInt(const std::string& text) {
    int val;
    std::cout << text;
    std::cin >> val;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод. Введите заново (int): ";
        std::cin >> val;
    }

    return val;
}

inline double ReadDouble(const std::string& text) {
    double val;
    std::cout << text;
    std::cin >> val;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод. Введите заново (double): ";
        std::cin >> val;
    }

    return val;
}

inline Complex ReadComplex(const std::string& text) {
    Complex val;
    std::cout << text;
    std::cin >> val.re >> val.im;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод. Введите заново (Complex): ";
        std::cin >> val.re >> val.im;
    }

    return val;
}

inline std::string ReadString(const std::string& text) {
    std::cout << text;
    std::string s;
    std::cin >> s;

    return s;
}
