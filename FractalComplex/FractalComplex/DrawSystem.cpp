#include "DrawSystem.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include "random.h"
#include "Cell.h"



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
}

void DrawSystem::drawInterface() {
	strokeRect(mouse.pos.x, mouse.pos.y, w/zoom, h/zoom, Color(255,255,255));
	strokeRect(mouse.pos.x+1, mouse.pos.y+1, w/zoom, h/zoom, Color(0,0,0));
}

void DrawSystem::createFractal(Vector2d box, int iterations, bool display) {
	values = {};
	for (int a = -box.x / 2; a < box.x / 2; a++) {
		values.push_back({});
		for (int b = -box.y / 2; b < box.y / 2; b++) {
			values.back().push_back(Cell());
		}
	}
	int x_pos = -1;
	int y_pos = -1;
	for (int a = -box.x / 2; a < box.x / 2; a++) {
		x_pos++;
		y_pos = -1;
		for (int b = -box.y / 2; b < box.y / 2; b++) {
			y_pos++;
			Complex x = Complex(a, b) * Complex(1 / cam.scale, 0) + Complex(cam.pos.x, cam.pos.y);
			Complex z = x;
			//calculating
			for (int i = 0; i < iterations; i++) {
				z = x  + z*z;
				long double r = geom::distance(Vector2d(), Vector2d(z.a, z.b));
				long double v = 0;
				if (r > 2000) {
					v = i * 0.001;
					values[x_pos][y_pos].a = v;
					values[x_pos][y_pos].b = r;
					break;
				}

			}
			
		}
		if (display && random::intRandom(0, box.x) < 30) {
			drawScene();
			fillRect(w / 2, h / 2, 100, 70, Color(255, 255, 255));
			double r = ((a + box.x / 2) / box.x * 100);
			fillRect(w / 2 - 50 + r / 2, h / 2, r, 70, Color(180, 180, 180));
			text(std::to_string(int(r)) + "%", w / 2, h / 2, 50, Color(0, 0, 0));
			window->display();
		}
	}
}

sf::Image DrawSystem::makeImage(Vector2d box, int iterations, bool display) {
	
	sf::Image image;
	image.create(box.x, box.y, sf::Color::Black);
	for (int x = 0; x < box.x; x++) {
		for (int y = 0; y < box.y; y++) {
			
			long double v = values[x][y].a*valueK;
			v += valueConst;//(0.5+sin(pow(2, (values[x][y] *5) + valueConst)))/2;
			while (v < 0) {
				v += 1;
			}
			while (v > 1) {
				v -= 1;
			}
			if (values[x][y].a == 0)
				v = 0;

			long double periodH = config->periodH;
			long double frequencyH = config->frequencyH;
			long double amplitudeH = config->amplitudeH;

			long double periodS = config->periodS;
			long double frequencyS = config->frequencyS;
			long double amplitudeS = config->amplitudeS;

			long double periodV = config->periodV;
			long double frequencyV = config->frequencyV;
			long double amplitudeV = config->amplitudeV;

			
			Color c = fromHSV(int((periodH + v * 360 * frequencyH ) * amplitudeH + colorConst) % 360,
				abs((sin(v * frequencyS * M_PI + periodS * M_PI) ) * amplitudeS + config->constantS),
				abs((sin(v * frequencyV * M_PI + periodV * M_PI) ) * amplitudeV + config->constantV)
			);
			int s = (int)(v*config->iterations);
			//c = fromHSV(int((periodH + v * 360 * frequencyH) * amplitudeH + colorConst) % 360, 1, values[x][y].b );
			
			if (v < EPS) {
				c = Color(0, 0, 0);
			}
			image.setPixel(x, y, sf::Color(c.r, c.g, c.b));

		}
	}
	return image;
}

void DrawSystem::setImage(bool display, bool createNew) {
	System& sys = *system;
	w = window->getSize().x;
	h = window->getSize().y;
	if(createNew)
		createFractal(Vector2d(w, h), config->iterations, display);
	img = makeImage(Vector2d(w, h), config->iterations, display);

	
}

void DrawSystem::draw() {
	System& sys = *system;
	window->clear();

	drawScene();
	
	drawInterface();
}
