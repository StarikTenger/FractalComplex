#include "DrawSystem.h"
#include <math.h>
#include <algorithm>

#include <iostream>

Color DrawSystem::fromHSV(long double H, long double S, long double V) {
	long double C = S * V;
	long double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	long double m = V - C;
	long double Rs, Gs, Bs;
	if (H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120) {
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	Color color;
	color.r = (Rs + m) * 255;
	color.g = (Gs + m) * 255;
	color.b = (Bs + m) * 255;
	return color;
}

void DrawSystem::fillRect(long double x, long double y, long double width, long double height, Color color) {
	sf::RectangleShape rectangle;
	rectangle.setOrigin(width / 2, height / 2);
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	rectangle.setPosition(x, y);
	window->draw(rectangle);
}

void DrawSystem::strokeRect(long double x, long double y, long double width, long double height, Color color) {
	sf::RectangleShape rectangle;
	rectangle.setOrigin(width / 2, height / 2);
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setOutlineColor(sf::Color(color.r, color.g, color.b, color.a));
	rectangle.setFillColor(sf::Color(0, 0, 0, 0));
	rectangle.setOutlineThickness(1 );
	rectangle.setPosition(x, y);
	window->draw(rectangle);
}

void DrawSystem::image(std::string name, long double x, long double y, long double width, long double height, long double angle, Color color) {
	sf::Texture& tex = *textures[name];
	Vector2d scale = { width / tex.getSize().x  , height / tex.getSize().y };
	Vector2d pos = { x, y };// cam.transform({ x, y });
	sf::Sprite sprite;
	sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
	sprite.setTexture(tex);
	sprite.setScale(scale.x, scale.y);
	sprite.setPosition(x, y);
	sprite.setColor(sf::Color(std::min(255, color.r), std::min(255, color.g), std::min(255, color.b), std::min(255, color.a)));
	sprite.setRotation(angle * 180 / M_PI);

	window->draw(sprite);
}

void DrawSystem::image(std::string name, long double x, long double y, long double width, long double height, long double angle) {
	image(name, x, y, width, height, angle, Color(255, 255, 255, 255));
}

void DrawSystem::image(std::string name, long double x, long double y, long double width, long double height, long double angle, long double d) {
	Vector2d pos(x, y);
	pos = cam.pos + (pos - cam.pos)*d;
	image(name, pos.x, pos.y, width*d, height*d, angle);
}



void DrawSystem::text(std::string text, long double x, long double y, int size, Color color) {
	sf::Text drawnText;
	drawnText.setFont(font);
	drawnText.setString(text);
	drawnText.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	drawnText.setCharacterSize(size);
	drawnText.setOrigin(floor(drawnText.getLocalBounds().width / 2), floor(drawnText.getLocalBounds().height ));
	drawnText.setPosition(x, y);
	window->draw(drawnText);
}