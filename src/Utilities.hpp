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

inline int func_inc(int x) {
    return x + 1;
}
inline int func_sqr(int x) {
    return x * x;
}
inline int func_abs(int x) {
    return (x < 0) ? -x : x;
}

inline Function ReadFunction(const std::string& text) {
    std::cout << text << '\n';
    std::cout << "1) f(x) = x + 1\n";
    std::cout << "2) f(x) = x * x\n";
    std::cout << "3) f(x) = |x|\n";

    int func_type = ReadInt("Выберите функцию (1-3): ");

    while (func_type < 1 || func_type > 3) {
        std::cout << "Некорректный ввод. Введите номер функции от 1 до 3\n";
        func_type = ReadInt("Выберите функцию (1-3): ");
    }

    if (func_type == 1) {
        return Function(&func_inc, "Инкремент");
    } else if (func_type == 2) {
        return Function(&func_sqr, "Квадрат");
    } else {
        return Function(&func_abs, "Модуль");
    }
}

inline Student ReadStudent(const std::string& text) {
    std::cout << text << '\n';

    int series = ReadInt("Серия паспорта: ");
    int number = ReadInt("Номер паспорта: ");
    PersonID student_id{series, number};

    std::string first_name = ReadString("Имя: ");
    std::string middle_name = ReadString("Отчество: ");
    std::string last_name = ReadString("Фамилия: ");

    int age = ReadInt("Возраст: ");

    int group_number = ReadInt("Номер группы: ");
    int admission_year = ReadInt("Год поступления: ");
    double average_grade = ReadDouble("Средняя оценка: ");

    return Student(student_id, first_name, middle_name, last_name, age, group_number, admission_year, average_grade);
}

inline Teacher ReadTeacher(const std::string& text) {
    std::cout << text << "\n";

    int series = ReadInt("Серия паспорта: ");
    int number = ReadInt("Номер паспорта: ");
    PersonID teacher_id{series, number};

    std::string first_name = ReadString("Имя: ");
    std::string middle_name = ReadString("Отчество: ");
    std::string last_name = ReadString("Фамилия: ");

    int age = ReadInt("Возраст: ");

    std::string subject = ReadString("Предмет: ");
    std::string faculty = ReadString("Факультет: ");

    return Teacher(teacher_id, first_name, middle_name, last_name, age, subject, faculty);
}
