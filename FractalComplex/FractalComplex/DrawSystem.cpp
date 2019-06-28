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
	
	System& sys = *system;
	w = window->getSize().x;
	h = window->getSize().y;
	
	window->setView(sf::View(sf::FloatRect(0, 0, w, h)));
	window->clear();
	
	sf::Texture tex;
	tex.loadFromImage(img);
	sf::Sprite spr;
	spr.setTexture(tex);
	window->draw(spr);
	//std::cout << "finished\n";
}

void DrawSystem::drawInterface() {
	strokeRect(mouse.pos.x, mouse.pos.y, w/zoom, h/zoom, Color(255,255,255));
	strokeRect(mouse.pos.x+1, mouse.pos.y+1, w/zoom, h/zoom, Color(0,0,0));
}

sf::Image DrawSystem::makeImage(Vector2d box, int iterations) {
	std::vector<std::vector<long double> > values;
	for (int a = -box.x / 2; a < box.x / 2; a++) {
		values.push_back({});
		for (int b = -box.y / 2; b < box.y / 2; b++) {
			Complex x = Complex(a, b) * Complex(1 / cam.scale, 0) + Complex(cam.pos.x, cam.pos.y);
			Complex z;
			values.back().push_back(0);
			for (int i = 0; i < iterations; i++) {
				z = x + z * z;
				long double r = geom::distance(Vector2d(), Vector2d(z.a, z.b));
				long double v = 0;
				if (r > 1000) {
					v = i * 1.0 / config->iterations;
					//fillRect(box.x/2 + a, box.y/2 + b, 1, 1, Color(v*25, v*v*2.5, v*v*v*0.25));
					values.back().back() = v;

					break;
				}

			}
		}
	}


	
	sf::Image image;
	image.create(box.x, box.y, sf::Color::Black);
	for (int x = 0; x < box.x; x++) {
		for (int y = 0; y < box.y; y++) {
			long double v = values[x][y];

			long double periodH = config->periodH;
			long double frequencyH = config->frequencyH;
			long double amplitudeH = config->amplitudeH;

			long double periodS = config->periodS;
			long double frequencyS = config->frequencyS;
			long double amplitudeS = config->amplitudeS;

			long double periodV = config->periodV;
			long double frequencyV = config->frequencyV;
			long double amplitudeV = config->amplitudeV;

			Color c = fromHSV(int((periodH + v * 360 * frequencyH) * amplitudeH) % 360,
				(sin(v * frequencyS * M_PI + periodS * M_PI) / 2 + 0.5) * amplitudeS + config->constantS,
				(sin(v * frequencyV * M_PI + periodV * M_PI) / 2 + 0.5) * amplitudeV + config->constantV
			);
			if (v < EPS) {
				c = Color(0, 0, 0);
			}
			image.setPixel(x, y, sf::Color(c.r, c.g, c.b));

		}
	}
	return image;
}

void DrawSystem::setImage() {
	std::cout << "fuck\n";
	System& sys = *system;
	w = window->getSize().x;
	h = window->getSize().y;
	img = makeImage(Vector2d(w, h), config->iterations);

	
}

void DrawSystem::draw() {
	System& sys = *system;
	window->clear();

	drawScene();
	
	drawInterface();
}
