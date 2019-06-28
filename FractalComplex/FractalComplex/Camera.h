#pragma once
#include "geometry.h"

class Camera{
public:
	Vector2d pos;
	Vector2d border;
	long double angle = 0;
	long double scale = 30;
	long double scaleVel = 2;
	Camera();
	Camera(Vector2d _pos, Vector2d _border, long double _scale);
	Vector2d transform(Vector2d p);
	~Camera();
};

