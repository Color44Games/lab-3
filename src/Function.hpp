#pragma once

#include "../sequence/Exceptions.hpp"

class Function {
public:
    using FuncPointer = int (*)(int);

private:
    FuncPointer funcPtr;
    const char* funcName;

public:
    // Конструкторы
    Function() : funcPtr(nullptr), funcName("") {}
    Function(FuncPointer func_ptr, const char* func_name) : funcPtr(func_ptr), funcName(func_name) {}

    // Геттеры
    FuncPointer GetFuncPtr() const {
        return this->funcPtr;
    }

    const char* GetFuncName() const {
        return this->funcName;
    }

    // Метод для вызова функции
    int call(int arg) const {
        if (funcPtr == nullptr) {
            throw RunTimeError("Function call error: attempt to call an undefined function");
        }

        return funcPtr(arg);
    }

    // Операторы
    bool operator==(const Function& other) const {
        return this->funcPtr == other.funcPtr;
    }

    bool operator!=(const Function& other) const {
        return !(*this == other);
    }
};