#pragma once
#include "Vector2d.h"
#include <vector>

# define M_PI   3.14159265358979323846  /* pi */
# define EPS    0.0001

namespace geom {
	bool isCross(Vector2d a, Vector2d b, Vector2d c, Vector2d d);
	Vector2d getCross(Vector2d a, Vector2d b, Vector2d c, Vector2d d);
	Vector2d direction(long double a);
	Vector2d direction(Vector2d  a, Vector2d  b);
	long double angle(Vector2d p);
	long double angle(Vector2d a, Vector2d b, Vector2d c);
	long double distance(Vector2d  a, Vector2d b);
	long double distance(Vector2d  p, Vector2d a, Vector2d b);
	Vector2d rotate(Vector2d p, long double angle);
	long double square(std::vector<Vector2d> polygon);
	bool inPolygon(Vector2d point, std::vector<Vector2d> polygon);
	std::vector<long double> angleDistribution(long double direction, long double width, int n);
}