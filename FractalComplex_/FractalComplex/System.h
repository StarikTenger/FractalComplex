#pragma once
#include <vector>
#include <fstream>
#include "Vector2d.h"
#include <string>
#include "Complex.h"


class System{
public:
	std::vector<std::vector<long double> > field;
	System();
	~System();
};