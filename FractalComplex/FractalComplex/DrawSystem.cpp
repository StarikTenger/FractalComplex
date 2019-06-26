#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>



DrawSystem::DrawSystem(){
	window = new sf::RenderWindow(sf::VideoMode(900, 600), "WINDOW");
	loadTextures();
}

DrawSystem::~DrawSystem(){}

void DrawSystem::drawScene() {
	std::cout << "fuck\n";
	System& sys = *system;
	w = window->getSize().x;
	h = window->getSize().y;
	//fillRect(0,0,100,100, Color(0, 255, 0));
	
	for (int a = -w/2; a < w/2; a++) {
		for (int b = -h/2; b < h/2; b++) {
			Complex x = Complex(a, b) * Complex(1/cam.scale, 0) + Complex(cam.pos.x, cam.pos.y);
			Complex z;
			for (int i = 0; i < 1000; i++) {
				z = x + z * z;
				if (geom::distance(Vector2d(), Vector2d(z.a, z.b)) > 2) {
					double v = i * 0.01;
					fillRect(w/2 + a, h/2 + b, 1, 1, Color(v*10, v*100, v*500));
					break;
				}
			}
		}
	}
}

void DrawSystem::drawInterface() {
	
}

void DrawSystem::draw() {
	System& sys = *system;
	window->clear();

	drawScene();
	
	drawInterface();
}
