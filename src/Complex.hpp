#pragma once

#include <cmath>

class Complex {
public:
    // Поля с данными
    double re;
    double im;

    // Конструкторы
    Complex() : re(0.0), im(0.0) {}
    Complex(double complex_re, double complex_im) : re(complex_re), im(complex_im) {}

    // Функция для нахождения модуля комплексного числа
    double Modulus() const {
        return std::sqrt(this->re * this->re + this->im * this->im);
    }

    // Операторы
    Complex operator+(const Complex& other) const {
        return Complex(this->re + other.re, this->im + other.im);
    }

    Complex operator-(const Complex& other) const {
        return Complex(this->re - other.re, this->im - other.im);
    }

    Complex operator*(const Complex& other) const {
        return Complex(this->re * other.re - this->im * other.im, this->re * other.im + this->im * other.re);
    }

    Complex& operator+=(const Complex& other) {
        this->re += other.re;
        this->im += other.im;

        return *this;
    }

    Complex& operator-=(const Complex& other) {
        this->re -= other.re;
        this->im -= other.im;

        return *this;
    }

    Complex& operator*=(const Complex& other) {
        double new_re = this->re * other.re - this->im * other.im;
        double new_im = this->re * other.im + this->im * other.re;

        this->re = new_re;
        this->im = new_im;

        return *this;
    }

    bool operator==(const Complex& other) const {
        return this->re == other.re && this->im == other.im;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
};