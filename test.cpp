#include <cmath>
#include <iostream>
#include <string>

#include "../src/Complex.hpp"
#include "../src/Matrix.hpp"
#include "../src/Queue.hpp"
#include "../src/Stack.hpp"
#include "../src/Utilities.hpp"


#ifdef _WIN32
#include <windows.h>
#endif

// Глобальные счетчики числа тестов
int total_tests_run = 0;
int total_tests_passed = 0;

// Вспомогательные функции для Map, Where, Reduce
int TestSquareFunc(int x) {
    return x * x;
}
bool TestEvenFunc(int x) {
    return x % 2 == 0;
}
int TestSumFunc(int acc, int x) {
    return acc + x;
}

// Функция для проверки условий
void AssertTest(bool condition, const std::string& test_name) {
    total_tests_run++;
    if (condition) {
        total_tests_passed++;
        std::cout << "[ OK ] " << test_name << std::endl;
    } else {
        std::cerr << "[FAIL] " << test_name << " (Условие не выполнено)" << std::endl;
    }
}

// ============================================================================
// ТЕСТЫ ДЛЯ СТЕКА
// ============================================================================

void TestStack_PushPop() {
    Stack<int> s;
    s.Push(10);
    s.Push(20);
    AssertTest(s.Pop() == 20 && s.Pop() == 10, "TestStack_1_PushPop");
}

void TestStack_Peek() {
    Stack<int> s;
    s.Push(50);
    AssertTest(s.Peek() == 50 && s.GetLength() == 1, "TestStack_2_Peek");
}

void TestStack_IsEmpty() {
    Stack<int> s;
    bool initial = s.IsEmpty();
    s.Push(1);
    bool after_push = s.IsEmpty();
    AssertTest(initial == true && after_push == false, "TestStack_3_IsEmpty");
}

void TestStack_GetLength() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    AssertTest(s.GetLength() == 3, "TestStack_4_GetLength");
}

void TestStack_ExceptionOnPop() {
    Stack<int> s;
    bool caught = false;
    try {
        s.Pop();
    } catch (const Exception& e) {
        caught = true;
    }
    AssertTest(caught == true, "TestStack_5_ExceptionOnPop");
}

void TestStack_Map() {
    Stack<int> s;
    s.Push(2);
    s.Push(3);
    Stack<int> mapped = s.Map(TestSquareFunc);
    AssertTest(mapped.Pop() == 9 && mapped.Pop() == 4, "TestStack_6_Map");
}

void TestStack_Where() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);
    Stack<int> filtered = s.Where(TestEvenFunc);
    AssertTest(filtered.GetLength() == 2 && filtered.Pop() == 4 && filtered.Pop() == 2, "TestStack_7_Where");
}

void TestStack_Reduce() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    int result = s.Reduce(TestSumFunc, 0);
    AssertTest(result == 6, "TestStack_8_Reduce");
}

void TestStack_Concat() {
    Stack<int> s1;
    s1.Push(1);
    Stack<int> s2;
    s2.Push(2);
    Stack<int> res = s1.Concat(s2);
    AssertTest(res.GetLength() == 2, "TestStack_9_Concat");
}

void TestStack_Subsequence() {
    Stack<int> s;
    s.Push(10);
    s.Push(20);
    s.Push(30);
    Stack<int> sub;
    sub.Push(20);
    sub.Push(30);
    int pos = s.FindSubsequence(sub);
    AssertTest(pos != -1, "TestStack_10_Subsequence");
}

// ============================================================================
// ТЕСТЫ ДЛЯ ОЧЕРЕДИ
// ============================================================================

void TestQueue_EnqueueDequeue() {
    Queue<int> q;
    q.Enqueue(10);
    q.Enqueue(20);
    AssertTest(q.Dequeue() == 10 && q.Dequeue() == 20, "TestQueue_11_EnqueueDequeue");
}

void TestQueue_Peek() {
    Queue<int> q;
    q.Enqueue(100);
    AssertTest(q.Peek() == 100 && q.GetLength() == 1, "TestQueue_12_Peek");
}

void TestQueue_IsEmpty() {
    Queue<int> q;
    bool initial = q.IsEmpty();
    q.Enqueue(5);
    bool after = q.IsEmpty();
    AssertTest(initial == true && after == false, "TestQueue_13_IsEmpty");
}

void TestQueue_GetLength() {
    Queue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    AssertTest(q.GetLength() == 2, "TestQueue_14_GetLength");
}

void TestQueue_ExceptionOnDequeue() {
    Queue<int> q;
    bool caught = false;
    try {
        q.Dequeue();
    } catch (const Exception& e) {
        caught = true;
    }
    AssertTest(caught == true, "TestQueue_15_ExceptionOnDequeue");
}

void TestQueue_Map() {
    Queue<int> q;
    q.Enqueue(3);
    q.Enqueue(4);
    Queue<int> mapped = q.Map(TestSquareFunc);
    AssertTest(mapped.Dequeue() == 9 && mapped.Dequeue() == 16, "TestQueue_16_Map");
}

void TestQueue_Where() {
    Queue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);
    Queue<int> filtered = q.Where(TestEvenFunc);
    AssertTest(filtered.GetLength() == 2 && filtered.Dequeue() == 2 && filtered.Dequeue() == 4, "TestQueue_17_Where");
}

void TestQueue_Reduce() {
    Queue<int> q;
    q.Enqueue(5);
    q.Enqueue(10);
    int result = q.Reduce(TestSumFunc, 0);
    AssertTest(result == 15, "TestQueue_18_Reduce");
}

void TestQueue_Concat() {
    Queue<int> q1;
    q1.Enqueue(1);
    Queue<int> q2;
    q2.Enqueue(2);
    Queue<int> res = q1.Concat(q2);
    AssertTest(res.GetLength() == 2 && res.Dequeue() == 1, "TestQueue_19_Concat");
}

void TestQueue_Subsequence() {
    Queue<int> q;
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    Queue<int> sub;
    sub.Enqueue(20);
    sub.Enqueue(30);
    int pos = q.FindSubsequence(sub);
    AssertTest(pos == 1, "TestQueue_20_Subsequence");
}

// ============================================================================
// ТЕСТЫ ДЛЯ МАТРИЦ
// ============================================================================

void TestMatrix_Creation() {
    RectangularMatrix<int> M(3, 4);
    AssertTest(M.GetRows() == 3 && M.GetCols() == 4, "TestMatrix_21_Creation");
}

void TestMatrix_Get() {
    RectangularMatrix<int> M(2, 2);
    M.Get(0, 1) = 45;
    AssertTest(M.Get(0, 1) == 45, "TestMatrix_22_Get");
}

void TestMatrix_Addition() {
    RectangularMatrix<int> M1(2, 2);
    M1.Get(0, 0) = 1;
    M1.Get(1, 1) = 2;
    RectangularMatrix<int> M2 = M1 + M1;
    AssertTest(M2.Get(0, 0) == 2 && M2.Get(1, 1) == 4, "TestMatrix_23_Addition");
}

void TestMatrix_ScalarMultiplication() {
    RectangularMatrix<int> M(2, 2);
    M.Get(0, 0) = 5;
    RectangularMatrix<int> res = M * 3;
    AssertTest(res.Get(0, 0) == 15, "TestMatrix_24_ScalarMultiplication");
}

void TestMatrix_MatrixMultiplication() {
    SquareMatrix<int> A(2);
    SquareMatrix<int> B(2);
    A.Get(0, 0) = 1;
    A.Get(0, 1) = 2;
    A.Get(1, 0) = 3;
    A.Get(1, 1) = 4;

    B.Get(0, 0) = 2;
    B.Get(0, 1) = 0;
    B.Get(1, 0) = 1;
    B.Get(1, 1) = 2;

    // Результат строки 0: (1*2 + 2*1) = 4, (1*0 + 2*2) = 4
    RectangularMatrix<int> C = A * B;
    AssertTest(C.Get(0, 0) == 4 && C.Get(0, 1) == 4, "TestMatrix_25_MatrixMultiplication");
}

void TestMatrix_Norm() {
    SquareMatrix<double> M(2);
    M.Get(0, 0) = 3.0;
    M.Get(0, 1) = 4.0;
    M.Get(1, 0) = 0.0;
    M.Get(1, 1) = 0.0;
    // Норма: sqrt(3 ** 2 + 4 ** 2) = 5.0
    AssertTest(std::abs(M.norm() - 5.0) < 1e-9, "TestMatrix_26_Norm");
}

void TestMatrix_SwapRows() {
    RectangularMatrix<int> M(2, 2);
    M.Get(0, 0) = 10;
    M.Get(1, 0) = 20;
    M.SwapRows(0, 1);
    AssertTest(M.Get(0, 0) == 20 && M.Get(1, 0) == 10, "TestMatrix_27_SwapRows");
}

void TestMatrix_MultiplyRow() {
    RectangularMatrix<int> M(2, 2);
    M.Get(0, 0) = 5;
    M.Get(0, 1) = 10;
    M.MultiplyRow(0, 2);
    AssertTest(M.Get(0, 0) == 10 && M.Get(0, 1) == 20, "TestMatrix_28_MultiplyRow");
}

void TestMatrix_SwapCols() {
    RectangularMatrix<int> M(2, 2);
    M.Get(0, 0) = 1;
    M.Get(0, 1) = 2;
    M.SwapCols(0, 1);
    AssertTest(M.Get(0, 0) == 2 && M.Get(0, 1) == 1, "TestMatrix_29_SwapCols");
}

void TestMatrix_MultiplyCol() {
    RectangularMatrix<int> M(2, 2);
    M.Get(0, 0) = 4;
    M.Get(1, 0) = 5;
    M.MultiplyCol(0, 3);
    AssertTest(M.Get(0, 0) == 12 && M.Get(1, 0) == 15, "TestMatrix_30_MultiplyCol");
}


// ============================================================================
// ЗАПУСК ТЕСТОВ
// ============================================================================
int main() {
    std::cout << "=== Тестирование Стека ===" << std::endl;
    TestStack_PushPop();
    TestStack_Peek();
    TestStack_IsEmpty();
    TestStack_GetLength();
    TestStack_ExceptionOnPop();
    TestStack_Map();
    TestStack_Where();
    TestStack_Reduce();
    TestStack_Concat();
    TestStack_Subsequence();

    std::cout << "\n=== Тестирование Очереди ===" << std::endl;
    TestQueue_EnqueueDequeue();
    TestQueue_Peek();
    TestQueue_IsEmpty();
    TestQueue_GetLength();
    TestQueue_ExceptionOnDequeue();
    TestQueue_Map();
    TestQueue_Where();
    TestQueue_Reduce();
    TestQueue_Concat();
    TestQueue_Subsequence();

    std::cout << "\n=== Тестирование Матриц ===" << std::endl;
    TestMatrix_Creation();
    TestMatrix_Get();
    TestMatrix_Addition();
    TestMatrix_ScalarMultiplication();
    TestMatrix_MatrixMultiplication();
    TestMatrix_Norm();
    TestMatrix_SwapRows();
    TestMatrix_MultiplyRow();
    TestMatrix_SwapCols();
    TestMatrix_MultiplyCol();

    std::cout << "\n=========================================" << std::endl;
    std::cout << "Итоги: " << std::endl;
    std::cout << "Всего тестов: " << total_tests_run << std::endl;
    std::cout << "Успешно пройдено:     " << total_tests_passed << " / " << total_tests_run << std::endl;

    if (total_tests_passed == total_tests_run) {
        std::cout << "Все тесты выполнены успешно." << std::endl;
    } else {
        std::cout << "Обнаружены ошибки." << std::endl;
    }

    std::cout << "=========================================" << std::endl;

    return (total_tests_passed == total_tests_run) ? 0 : 1;
}