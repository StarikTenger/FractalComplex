#pragma once
class Complex {
public:
	double a;
	double b;

	Complex();
	Complex(double _a, double _b);
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

