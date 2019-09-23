#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "geometry.h"

class Frame {
public:
	sf::Image image;
	Vector2d pos;
	std::vector<std::vector<Cell> > values;
	double scale;
	Frame();
	~Frame();
};

