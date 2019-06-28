#pragma once
class Vector2d {
public:
	long double x=0, y=0;
	Vector2d() {};
	Vector2d(long double x1, long double y1);
};

Vector2d operator+(const Vector2d& a, const Vector2d& b);
Vector2d operator-(const Vector2d& a, const Vector2d& b);
Vector2d operator*(const Vector2d& a, long double k);
Vector2d operator/(const Vector2d& a, long double k);
Vector2d operator+=(Vector2d& a, const Vector2d& b);
Vector2d operator-=(Vector2d& a, const Vector2d& b);