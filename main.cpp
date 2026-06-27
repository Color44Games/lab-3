#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

#include "../sequence/Exceptions.hpp"
#include "../src/Complex.hpp"
#include "../src/Function.hpp"
#include "../src/Matrix.hpp"
#include "../src/Person.hpp"
#include "../src/Queue.hpp"
#include "../src/Stack.hpp"
#include "../src/Utilities.hpp"

#ifdef _WIN32
#include <windows.h>
#undef GetMessage
#endif

// ============================================================================
// ЧТЕНИЕ ТИПОВ ДАННЫХ
// ============================================================================
template <class T>
T ReadValue(const std::string& text);

template <>
inline int ReadValue<int>(const std::string& text) {
    return ReadInt(text);
}

template <>
inline double ReadValue<double>(const std::string& text) {
    return ReadDouble(text);
}

template <>
inline Complex ReadValue<Complex>(const std::string& text) {
    std::cout << text << "\n";
    double re = ReadDouble("Действительная часть (re): ");
    double im = ReadDouble("Мнимая часть (im): ");

    return Complex(re, im);
}

template <>
inline std::string ReadValue<std::string>(const std::string& text) {
    return ReadString(text);
}

template <>
inline Student ReadValue<Student>(const std::string& text) {
    return ReadStudent(text);
}

template <>
inline Teacher ReadValue<Teacher>(const std::string& text) {
    return ReadTeacher(text);
}

// ============================================================================
// ФУНКЦИИ ДЛЯ Map, Where, Reduce
// ============================================================================
inline int int_square(int x) {
    return x * x;
}
inline bool int_is_even(int x) {
    return x % 2 == 0;
}
inline int int_sum(int x, int y) {
    return x + y;
}

inline double double_mul2(double x) {
    return x * 2.0;
}
inline bool double_is_positive(double x) {
    return x > 0.0;
}
inline double double_sum(double x, double y) {
    return x + y;
}

inline Complex complex_conj(Complex c) {
    return Complex(c.re, -c.im);
}
inline bool complex_mod_bigger_5(Complex c) {
    return c.Modulus() > 5.0;
}
inline Complex complex_sum(Complex c1, Complex c2) {
    return c1 + c2;
}

inline std::string string_reverse(std::string s) {
    std::reverse(s.begin(), s.end());
    return s;
}
inline bool string_longer_3(std::string s) {
    return s.length() > 3;
}
inline std::string string_concat(std::string s1, std::string s2) {
    return s1 + s2;
}

// ============================================================================
// МЕНЮ ОПЕРАЦИЙ ДЛЯ МАТРИЦ, СТЭКА И ОЧЕРЕДИ
// ============================================================================

// Подменю матриц
template <class T>
void MatrixMenu() {
    RectangularMatrix<T>* rect_mat = nullptr;
    SquareMatrix<T>* sqr_mat = nullptr;
    int command = -1;

    while (command != 0) {
        std::cout << "\n===== Операции с матрицами =====" << std::endl;
        std::cout << "1) Создать прямоугольную матрицу" << std::endl;
        std::cout << "2) Создать квадратную матрицу" << std::endl;
        std::cout << "3) Распечатать прямоугольную матрицу" << std::endl;
        std::cout << "4) Распечатать квадратную матрицу" << std::endl;
        std::cout << "5) Получить элемент прямоугольной матрицы (i,j)" << std::endl;
        std::cout << "6) Получить элемент квадратной матрицы (i,j)" << std::endl;
        std::cout << "7) Сложение прямоугольных матриц (матрица + сама она)" << std::endl;
        std::cout << "8) Умножение прямоугольной матрицы на скаляр" << std::endl;
        std::cout << "9) Матричное умножение прямоугольной матрицы на саму себя" << std::endl;
        std::cout << "10) Норма прямоугольной матрицы" << std::endl;
        std::cout << "11) Норма квадратной матрицы" << std::endl;
        std::cout << "12) Поменять местами строки в прямоугольной матрице" << std::endl;
        std::cout << "13) Умножить строку в прямоугольной матрице на скаляр" << std::endl;
        std::cout << "14) Поменять местами столбцы в прямоугольной матрице" << std::endl;
        std::cout << "15) Умножить столбец в прямоугольной матрице на скаляр" << std::endl;
        std::cout << "0) Выйти в главное меню" << std::endl;

        command = ReadInt("Ваш выбор: ");

        switch (command) {
            case 1: {
                try {
                    delete rect_mat;
                    rect_mat = nullptr;
                    int rows = ReadInt("Количество строк: ");
                    int cols = ReadInt("Количество столбцов: ");
                    rect_mat = new RectangularMatrix<T>(rows, cols);

                    std::cout << "Введите элементы по строкам:" << "\n";
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                            std::cout << "  Элемент(" << i << "," << j << "): ";
                            rect_mat->Get(i, j) = ReadValue<T>("");
                        }
                    }

                    std::cout << "Прямоугольная матрица успешно создана." << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 2: {
                try {
                    delete sqr_mat;
                    sqr_mat = nullptr;
                    int size = ReadInt("Размер матрицы: ");
                    sqr_mat = new SquareMatrix<T>(size);

                    std::cout << "Введите элементы по строкам:" << "\n";
                    for (int i = 0; i < size; i++) {
                        for (int j = 0; j < size; j++) {
                            std::cout << "  Элемент(" << i << "," << j << "): ";
                            sqr_mat->Get(i, j) = ReadValue<T>("");
                        }
                    }

                    std::cout << "Квадратная матрица успешно создана." << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 3:
                try {
                    if (!rect_mat) {
                        std::cout << "Прямоугольная матрица не создана." << "\n";
                        break;
                    }

                    std::cout << "Прямоугольная матрица:" << "\n";
                    PrintMatrix(*rect_mat);
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 4:
                try {
                    if (!sqr_mat) {
                        std::cout << "Квадратная матрица не создана." << "\n";
                        break;
                    }

                    std::cout << "Квадратная матрица:" << "\n";
                    PrintMatrix(*sqr_mat);
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 5: {
                try {
                    if (!rect_mat) {
                        std::cout << "Прямоугольная матрица не создана." << "\n";
                        break;
                    }

                    int row_index = ReadInt("Индекс строки: ");
                    int col_index = ReadInt("Индекс столбца: ");
                    std::cout << "Элемент(" << row_index << "," << col_index
                              << ") = " << rect_mat->Get(row_index, col_index) << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 6: {
                try {
                    if (!sqr_mat) {
                        std::cout << "Квадратная матрица не создана." << "\n";
                        break;
                    }

                    int row_index = ReadInt("Индекс строки: ");
                    int col_index = ReadInt("Индекс столбца: ");
                    std::cout << "Элемент(" << row_index << "," << col_index
                              << ") = " << sqr_mat->Get(row_index, col_index) << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 7: {
                try {
                    if (!rect_mat) {
                        std::cout << "Прямоугольная матрица не создана." << "\n";
                        break;
                    }

                    RectangularMatrix<T> sum = *rect_mat + *rect_mat;
                    std::cout << "Результат сложения матрицы с самой собой:" << "\n";
                    PrintMatrix(sum);
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 8: {
                try {
                    if (!rect_mat) {
                        std::cout << "Прямоугольная матрица не создана." << "\n";
                        break;
                    }

                    T scalar = ReadValue<T>("Скаляр: ");
                    RectangularMatrix<T> prod = *rect_mat * scalar;
                    std::cout << "Результат умножения на скаляр:" << "\n";
                    PrintMatrix(prod);
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 9: {
                try {
                    if (!rect_mat) {
                        std::cout << "Прямоугольная матрица не создана." << "\n";
                        break;
                    }

                    if (rect_mat->GetRows() != rect_mat->GetCols()) {
                        std::cout << "Прямоугольная матрица не является квадратной, невозможно вычислить умножение на "
                                     "саму себя."
                                  << "\n";
                        break;
                    }

                    RectangularMatrix<T> prod = (*rect_mat) * (*rect_mat);
                    std::cout << "Результат умножения матрицы на саму себя:" << "\n";
                    PrintMatrix(prod);
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 10:
                try {
                    if (!rect_mat) {
                        std::cout << "Прямоугольная матрица не создана." << "\n";
                        break;
                    }

                    std::cout << "Норма прямоугольной матрицы = " << rect_mat->norm() << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 11:
                try {
                    if (!sqr_mat) {
                        std::cout << "Квадратная матрица не создана." << "\n";
                        break;
                    }

                    std::cout << "Норма квадратной матрицы = " << sqr_mat->norm() << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 12: {
                try {
                    if (!rect_mat) {
                        std::cout << "Прямоугольная матрица не создана." << "\n";
                        break;
                    }

                    int r1 = ReadInt("Индекс первой строки: ");
                    int r2 = ReadInt("Индекс второй строки: ");
                    rect_mat->SwapRows(r1, r2);
                    std::cout << "Строки успешно поменяны местами." << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 13: {
                try {
                    if (!rect_mat) {
                        std::cout << "Прямоугольная матрица не создана." << "\n";
                        break;
                    }

                    int row_index = ReadInt("Индекс строки: ");
                    T scalar = ReadValue<T>("Скаляр: ");
                    rect_mat->MultiplyRow(row_index, scalar);
                    std::cout << "Строка успешно умножена." << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 14: {
                try {
                    if (!rect_mat) {
                        std::cout << "Прямоугольная матрица не создана." << "\n";
                        break;
                    }

                    int c1 = ReadInt("Индекс первого столбца: ");
                    int c2 = ReadInt("Индекс второго столбца: ");
                    rect_mat->SwapCols(c1, c2);
                    std::cout << "Столбцы успешно поменяны местами." << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 15: {
                try {
                    if (!rect_mat) {
                        std::cout << "Прямоугольная матрица не создана." << "\n";
                        break;
                    }

                    int col_index = ReadInt("Индекс столбца: ");
                    T scalar = ReadValue<T>("Скаляр: ");
                    rect_mat->MultiplyCol(col_index, scalar);
                    std::cout << "Столбец успешно умножен." << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Неверный номер команды.\n";
        }
    }

    delete rect_mat;
    delete sqr_mat;
}

// Подменю очереди
template <class T>
void QueueMenu(T (*MapFunc)(T), bool (*WhereFunc)(T), T (*ReduceFunc)(T, T), const T& initReduce) {
    Queue<T> queue;
    int command = -1;

    while (command != 0) {
        std::cout << "\n===== Операции с очередью =====" << std::endl;
        std::cout << "1) Enqueue (Добавить элемент в конец)" << std::endl;
        std::cout << "2) Dequeue (Удалить элемент из начала)" << std::endl;
        std::cout << "3) Peek (Посмотреть первый элемент)" << std::endl;
        std::cout << "4) IsEmpty (Проверить на пустоту)" << std::endl;
        std::cout << "5) GetLength (Текущая длина очереди)" << std::endl;
        std::cout << "6) Распечатать очередь" << std::endl;
        std::cout << "7) Map" << std::endl;
        std::cout << "8) Where (Фильтрация)" << std::endl;
        std::cout << "9) Reduce (Суммирование)" << std::endl;
        std::cout << "10) Конкатенация" << std::endl;
        std::cout << "11) Взять подпоследовательность" << std::endl;
        std::cout << "12) Найти подпоследовательность" << std::endl;
        std::cout << "0) Выйти в главное меню" << std::endl;

        command = ReadInt("Ваш выбор: ");

        switch (command) {
            case 1:
                try {
                    queue.Enqueue(ReadValue<T>("Значение для добавления: "));
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 2:
                try {
                    std::cout << "Извлечен элемент: " << queue.Dequeue() << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 3:
                try {
                    std::cout << "В начале очереди: " << queue.Peek() << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 4:
                try {
                    std::cout << (queue.IsEmpty() ? "Очередь пуста.\n" : "В очереди есть элементы.\n");
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 5:
                try {
                    std::cout << "Длина: " << queue.GetLength() << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 6:
                try {
                    PrintQueue(queue);
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 7:
                try {
                    if (!MapFunc) {
                        std::cout << "Операция Map недоступна для объектов такого типа.\n";
                        break;
                    }

                    std::cout << "После Map: ";
                    PrintQueue(queue.Map(MapFunc));
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 8:
                try {
                    if (!WhereFunc) {
                        std::cout << "Операция Where недоступна для объектов такого типа.\n";
                        break;
                    }

                    std::cout << "После Where: ";
                    PrintQueue(queue.Where(WhereFunc));
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 9:
                try {
                    if (!ReduceFunc) {
                        std::cout << "Операция Reduce недоступна для объектов такого типа.\n";
                        break;
                    }

                    std::cout << "Результат свертки Reduce: " << queue.Reduce(ReduceFunc, initReduce) << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 10: {
                try {
                    Queue<T> other;
                    int cnt = ReadInt("Сколько элементов ввести для второй очереди? ");

                    for (int i = 0; i < cnt; i++) {
                        other.Enqueue(ReadValue<T>("Значение: "));
                    }

                    std::cout << "Результат конкатенации: ";
                    PrintQueue(queue.Concat(other));
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 11: {
                try {
                    int start_index = ReadInt("Стартовый индекс: ");
                    int end_index = ReadInt("Конечный индекс: ");

                    std::cout << "Подпоследовательность: ";
                    PrintQueue(queue.GetSubsequence(start_index, end_index));
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 12: {
                try {
                    Queue<T> sub;
                    int cnt = ReadInt("Длина искомой подпоследовательности: ");

                    for (int i = 0; i < cnt; i++) {
                        sub.Enqueue(ReadValue<T>("Значение подпоследовательности: "));
                    }

                    int pos = queue.FindSubsequence(sub);
                    if (pos != -1) {
                        std::cout << "Подпоследовательность найдена. Начальный индекс: " << pos << "\n";
                    } else {
                        std::cout << "Подпоследовательность не найдена.\n";
                    }
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Неверный номер команды.\n";
        }
    }
}

// Подменю стека
template <class T>
void StackMenu(T (*MapFunc)(T), bool (*WhereFunc)(T), T (*ReduceFunc)(T, T), const T& initReduce) {
    Stack<T> stack;
    int command = -1;

    while (command != 0) {
        std::cout << "\n===== Операции со стеком =====" << std::endl;
        std::cout << "1) Push" << std::endl;
        std::cout << "2) Pop" << std::endl;
        std::cout << "3) Peek (Посмотреть верхний элемент) " << std::endl;
        std::cout << "4) IsEmpty (Проверить на пустоту)" << std::endl;
        std::cout << "5) GetLength (Текущая длина стека)" << std::endl;
        std::cout << "6) Распечатать стек" << std::endl;
        std::cout << "7) Map" << std::endl;
        std::cout << "8) Where (Фильтрация)" << std::endl;
        std::cout << "9) Reduce (Суммирование)" << std::endl;
        std::cout << "10) Конкатенация" << std::endl;
        std::cout << "11) Взять подпоследовательность" << std::endl;
        std::cout << "12) Найти подпоследовательность" << std::endl;
        std::cout << "0) Выйти в главное меню" << std::endl;

        command = ReadInt("Ваш выбор: ");

        switch (command) {
            case 1:
                try {
                    stack.Push(ReadValue<T>("Значение для добавления: "));
                    std::cout << "Элемент успешно добавлен.\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 2:
                try {
                    std::cout << "Извлечен элемент: " << stack.Pop() << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 3:
                try {
                    std::cout << "Вершина стека: " << stack.Peek() << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 4:
                try {
                    std::cout << (stack.IsEmpty() ? "Стек пуст.\n" : "В стеке есть элементы.\n");
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 5:
                try {
                    std::cout << "Длина: " << stack.GetLength() << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 6:
                try {
                    PrintStack(stack);
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 7:
                try {
                    if (!MapFunc) {
                        std::cout << "Операция Map недоступна для объектов такого типа.\n";
                        break;
                    }
                    std::cout << "После Map: ";
                    PrintStack(stack.Map(MapFunc));
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 8:
                try {
                    if (!WhereFunc) {
                        std::cout << "Операция Where недоступна для объектов такого типа.\n";
                        break;
                    }
                    std::cout << "После Where: ";
                    PrintStack(stack.Where(WhereFunc));
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 9:
                try {
                    if (!ReduceFunc) {
                        std::cout << "Операция Reduce недоступна для объектов такого типа.\n";
                        break;
                    }
                    std::cout << "Результат Reduce: " << stack.Reduce(ReduceFunc, initReduce) << "\n";
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            case 10: {
                try {
                    Stack<T> other;
                    int cnt = ReadInt("Количество элементов во втором стэке: ");

                    for (int i = 0; i < cnt; i++) {
                        other.Push(ReadValue<T>("Значение: "));
                    }

                    std::cout << "Результат конкатенации: ";
                    PrintStack(stack.Concat(other));
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 11: {
                try {
                    int start_index = ReadInt("Стартовый индекс: ");
                    int end_index = ReadInt("Конечный индекс: ");

                    std::cout << "Подпоследовательность: ";
                    PrintStack(stack.GetSubsequence(start_index, end_index));
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 12: {
                try {
                    Stack<T> sub;
                    int cnt = ReadInt("Длина искомой подпоследовательности: ");

                    for (int i = 0; i < cnt; i++) {
                        sub.Push(ReadValue<T>("Значение подпоследовательности: "));
                    }

                    int pos = stack.FindSubsequence(sub);
                    if (pos != -1) {
                        std::cout << "Подпоследовательность найдена. Начальный индекс: " << pos << "\n";
                    } else {
                        std::cout << "Подпоследовательность не найдена.\n";
                    }
                } catch (const Exception& e) {
                    std::cout << "Ошибка: " << e.GetMessage() << "\n";
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Неверный номер команды.\n";
        }
    }
}


// ============================================================================
// СЕЛЕКТОРЫ ТИПОВ ДАННЫХ
// ============================================================================
void ChooseTypeForMatrix() {
    int command = -1;

    while (command != 0) {
        std::cout << "\n=== Выбор типа элементов матрицы ===" << std::endl;
        std::cout << "1) Целые числа (int)" << std::endl;
        std::cout << "2) Вещественные числа (double)" << std::endl;
        std::cout << "3) Комплексные числа (Complex)" << std::endl;
        std::cout << "0) Выход в главное меню" << std::endl;

        command = ReadInt("Ваш выбор: ");

        switch (command) {
            case 1:
                MatrixMenu<int>();
                break;
            case 2:
                MatrixMenu<double>();
                break;
            case 3:
                MatrixMenu<Complex>();
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный вариант.\n";
        }
    }
}

void ChooseTypeForQueue() {
    int command = -1;

    while (command != 0) {
        std::cout << "\n=== Выбор типа элементов очереди ===" << std::endl;
        std::cout << "1) Целые числа (int)" << std::endl;
        std::cout << "2) Вещественные числа (double)" << std::endl;
        std::cout << "3) Комплексные числа (Complex)" << std::endl;
        std::cout << "4) Строки (std::string)" << std::endl;
        std::cout << "5) Данные Студентов (Student)" << std::endl;
        std::cout << "6) Данные Преподавателей (Teacher)" << std::endl;
        std::cout << "0) Выход в главное меню" << std::endl;

        command = ReadInt("Ваш выбор: ");

        switch (command) {
            case 1:
                QueueMenu<int>(int_square, int_is_even, int_sum, 0);
                break;
            case 2:
                QueueMenu<double>(double_mul2, double_is_positive, double_sum, 0.0);
                break;
            case 3:
                QueueMenu<Complex>(complex_conj, complex_mod_bigger_5, complex_sum, Complex(0, 0));
                break;
            case 4:
                QueueMenu<std::string>(string_reverse, string_longer_3, string_concat, "");
                break;
            case 5:
                QueueMenu<Student>(nullptr, nullptr, nullptr, Student());
                break;
            case 6:
                QueueMenu<Teacher>(nullptr, nullptr, nullptr, Teacher());
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный вариант.\n";
        }
    }
}

void ChooseTypeForStack() {
    int command = -1;

    while (command != 0) {
        std::cout << "\n=== Выбор типа элементов Стека ===" << std::endl;
        std::cout << "1) Целые числа (int)" << std::endl;
        std::cout << "2) Вещественные числа (double)" << std::endl;
        std::cout << "3) Комплексные числа (Complex)" << std::endl;
        std::cout << "4) Строки (std::string)" << std::endl;
        std::cout << "5) Данные Студентов (Student)" << std::endl;
        std::cout << "6) Данные Преподавателей (Teacher)" << std::endl;
        std::cout << "0) Выход в главное меню" << std::endl;

        command = ReadInt("Ваш выбор: ");

        switch (command) {
            case 1:
                StackMenu<int>(int_square, int_is_even, int_sum, 0);
                break;
            case 2:
                StackMenu<double>(double_mul2, double_is_positive, double_sum, 0.0);
                break;
            case 3:
                StackMenu<Complex>(complex_conj, complex_mod_bigger_5, complex_sum, Complex(0, 0));
                break;
            case 4:
                StackMenu<std::string>(string_reverse, string_longer_3, string_concat, "");
                break;
            case 5:
                StackMenu<Student>(nullptr, nullptr, nullptr, Student());
                break;
            case 6:
                StackMenu<Teacher>(nullptr, nullptr, nullptr, Teacher());
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный вариант.\n";
        }
    }
}

// ============================================================================
// ОСНОВНОЕ МЕНЮ
// ============================================================================

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    int mainCommand = -1;

    while (mainCommand != 0) {
        std::cout << "\n=======================================" << std::endl;
        std::cout << "        ГЛАВНОЕ УПРАВЛЯЮЩЕЕ МЕНЮ        " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1) Работа с матрицей" << std::endl;
        std::cout << "2) Работа с очередью" << std::endl;
        std::cout << "3) Работа с стеком" << std::endl;
        std::cout << "0) Завершить выполнение программы" << std::endl;
        std::cout << "========================================" << std::endl;

        mainCommand = ReadInt("Ваш выбор: ");

        switch (mainCommand) {
            case 1:
                ChooseTypeForMatrix();
                break;
            case 2:
                ChooseTypeForQueue();
                break;
            case 3:
                ChooseTypeForStack();
                break;
            case 0:
                std::cout << "Программа успешно завершена.\n";
                break;
            default:
                std::cout << "Неверный номер команды.\n";
        }
    }

    return 0;
}