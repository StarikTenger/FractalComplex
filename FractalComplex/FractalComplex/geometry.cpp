#pragma once
#include "geometry.h"
#include <math.h>
#include <algorithm>

bool IsLinesCross(long double p0_x, long double p0_y, long double p1_x, long double p1_y, long double p2_x, long double p2_y, long double p3_x, long double p3_y, long double &i_x, long double &i_y)
{
	long double s1_x, s1_y, s2_x, s2_y;
	s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
	s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

	long double s, t;
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		//if (i_x != NULL)
		i_x = p0_x + (t * s1_x);
		//if (i_y != NULL)
		i_y = p0_y + (t * s1_y);
		return 1;
	}


	return 0; // No collision
}
bool geom::isCross(Vector2d a, Vector2d b, Vector2d c, Vector2d d) {
	long double x, y;
	return IsLinesCross(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y, x, y);
}
Vector2d geom::getCross(Vector2d a, Vector2d b, Vector2d c, Vector2d d) {
	Vector2d p;
	IsLinesCross(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y, p.x, p.y);
	return p;
}
Vector2d geom::direction(long double a) {
	return Vector2d(cos(a), sin(a));
}
Vector2d geom::direction(Vector2d a, Vector2d b) {
	if (abs((a - b).x) < EPS && abs((a - b).y) < EPS)
		return {};
	return (a - b) / distance(a, b);
}
long double geom::angle(Vector2d p) {
	if (abs(p.x) < EPS && abs(p.y) < EPS) {
		return 0;
	}
	p = p / distance(p, Vector2d(0, 0));
	long double direction = asin(p.y);
	if (p.x < 0) {
		direction = M_PI - direction;
	}

	return direction;
}
long double geom::angle(Vector2d a, Vector2d b, Vector2d c) {
	long double sA, sB, sC; //sides
	sA = distance(c, b);
	sB = distance(a, c);
	sC = distance(a, b);
	return acos((sA*sA + sC * sC - sB * sB) / 2 / sA / sC);
}
long double geom::distance(Vector2d  a, Vector2d  b) {
	Vector2d d = a - b;
	return sqrt(d.x*d.x + d.y*d.y);
}
long double geom::distance(Vector2d  p, Vector2d a, Vector2d b) {
	long double ang = angle(p, a, b);
	return distance(p, a)*sin(ang);
}
Vector2d geom::rotate(Vector2d p, long double angle) {
	Vector2d p1;
	p1.x = p.x * cos(angle) - p.y * sin(angle);
	p1.y = p.x * sin(angle) + p.y * cos(angle);
	return p1;
}
long double geom::square(std::vector<Vector2d> polygon) {
	long double s = 0;;
	for (int i = 0; i < polygon.size(); i++) {
		int j = (i + 1) % polygon.size();
		s += polygon[i].x*polygon[j].y;
		s -= polygon[j].x*polygon[i].y;
	}
	s = abs(s) / 2;
	return s;
}
bool geom::inPolygon(Vector2d point, std::vector<Vector2d> polygon) {
	Vector2d p1 = point + Vector2d(10000, 0);
	int counter = 0;
	for (int i = 0; i < polygon.size(); i++) {
		int j = i - 1;
		if (j < 0) {
			j = polygon.size() - 1;
		}
		if (isCross(point, p1, polygon[i], polygon[j]))
			counter++;
	}
	return counter % 2;
}
std::vector<long double> geom::angleDistribution(long double direction, long double width, int n) {
	std::vector<long double> arr;
	long double da = width / (long double)n;
	for (int i = 0; i < n; i++) {
		long double a = direction - width / 2.0 + da / 2.0 + da * (long double)i;
		arr.push_back(a);
	}
	return arr;
}