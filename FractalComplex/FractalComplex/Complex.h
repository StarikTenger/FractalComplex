#pragma once
class Complex {
public:
	long double a;
	long double b;

	Complex();
	Complex(long double _a, long double _b);
	~Complex();
};

Complex operator+(const Complex& a, const Complex& b);
Complex operator-(const Complex& a, const Complex& b);
Complex operator*(const Complex& a, const Complex& b);
Complex operator/(const Complex& a, const Complex& b);
Complex operator+=(Complex& a, const Complex& b);
Complex operator-=(Complex& a, const Complex& b);
Complex operator*=(Complex& a, const Complex& b);
Complex operator/=(Complex& a, const Complex& b);

