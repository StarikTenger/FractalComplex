#include "Complex.h"

Complex::Complex() {
	a = b = 0;
}

Complex::Complex(long double _a, long double _b) {
	a = _a;
	b = _b;
}

Complex::~Complex() {

}

Complex operator+(const Complex& a, const Complex& b) {
	return Complex(a.a + b.a, a.b + b.b);
}

Complex operator-(const Complex& a, const Complex& b) {
	return Complex(a.a - b.a, a.b - b.b);
}

Complex operator*(const Complex& a, const Complex& b) {
	return Complex(a.a*b.a - a.b*b.b, a.a*b.b + a.b*b.a);
}
Complex operator/(const Complex& a, const Complex& b) {
	Complex b1(b.a/(b.a*b.a + b.b*b.b), -b.b/ (b.a * b.a + b.b * b.b));
	return a * b1;
}
Complex operator+=(Complex& a, const Complex& b) {
	return a = a + b;
}
Complex operator-=(Complex& a, const Complex& b) {
	return a = a - b;
}
Complex operator*=(Complex& a, const Complex& b) {
	return a = a * b;
}
Complex operator/=(Complex& a, const Complex& b) {
	return a = a / b;
}