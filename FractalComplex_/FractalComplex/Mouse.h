#pragma once
#include "Vector2d.h"

class Mouse{
public:
	Vector2d pos;
	bool state = 0;
	bool statePrev = 0;
	double delta = 0;
	Mouse();
	~Mouse();
};

