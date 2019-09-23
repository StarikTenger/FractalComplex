#pragma once
#include <SFML/Graphics.hpp>
#include "geometry.h"

class Frame {
public:
	sf::Image image;
	Vector2d pos;
	double zoom;
	Frame();
	~Frame();
};

