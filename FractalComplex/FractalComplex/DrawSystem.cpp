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

void DrawSystem::setImage() {
	std::cout << "fuck\n";
	System& sys = *system;
	w = window->getSize().x;
	h = window->getSize().y;


	//fillRect(0,0,100,100, Color(0, 255, 0));
	double rMax = 0;
	double iMax = 0;
	std::vector<std::vector<double> > values;
	for (int a = -w / 2; a < w / 2; a++) {
		values.push_back({});
		for (int b = -h / 2; b < h / 2; b++) {
			Complex x = Complex(a, b) * Complex(1 / cam.scale, 0) + Complex(cam.pos.x, cam.pos.y);
			Complex z;
			values.back().push_back(0);
			for (int i = 0; i < config->iterations; i++) {
				z = x + z * z;
				double r = geom::distance(Vector2d(), Vector2d(z.a, z.b));
				if (r > rMax) {
					rMax = r;
				}
				double v = 0;
				if (r > 1000) {
					if (i > iMax) {
						iMax = i;
					}
					v = i * 1.0 / config->iterations;
					//fillRect(w/2 + a, h/2 + b, 1, 1, Color(v*25, v*v*2.5, v*v*v*0.25));
					values.back().back() = v;

					break;
				}

			}
		}
	}


	std::cout << iMax << "\n";
	window->setView(sf::View(sf::FloatRect(0, 0, w, h)));
	window->clear();
	img.create(w, h, sf::Color::Black);
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			double v = values[x][y];

			double periodH = config->periodH;
			double frequencyH = config->frequencyH;
			double amplitudeH = config->amplitudeH;

			double periodS = config->periodS;
			double frequencyS = config->frequencyS;
			double amplitudeS = config->amplitudeS;

			double periodV = config->periodV;
			double frequencyV = config->frequencyV;
			double amplitudeV = config->amplitudeV;

			Color c = fromHSV(int((periodH + v * 360 * frequencyH)*amplitudeH) % 360, 
				(sin(v * frequencyS * M_PI + periodS * M_PI) / 2 + 0.5) * amplitudeS,
				(sin(v * frequencyV * M_PI + periodV * M_PI) / 2 + 0.5) * amplitudeV
			);
			if (v < EPS) {
				c = Color(0, 0, 0);
			}
			img.setPixel(x, y, sf::Color(c.r, c.g, c.b));

		}
	}
}

void DrawSystem::draw() {
	System& sys = *system;
	window->clear();

	drawScene();
	
	drawInterface();
}
