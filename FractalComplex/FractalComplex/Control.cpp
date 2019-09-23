#include "Control.h"
#include "getMilliCount.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "random.h"

Control::Control() {
	for (int i = 0; i < 100; i++) {
		keyMatches.push_back({});
	}
	std::ifstream keys("keys.conf");
	while (keys) {
		std::string key;
		keys >> key;
		while (keys) {
			std::string key1;
			keys >> key1;
			if (key1 == "END")
				break;
			keyMatches[getKey(key1)].push_back(getKey(key));
			
		}
	}
	config = Config("config.conf");
	drawSys.config = &config;
	//////////////////////////////////////////
	Camera& cam = drawSys.cam;
	cam.pos = { -0.5, 0 };
	cam.scale = drawSys.window->getSize().y / 4;
	drawSys.system = &sys;
	drawSys.setImage(0, 1);
	Frame frame;
	frame.image = drawSys.img;
	frame.pos = drawSys.cam.pos;
	frame.scale = drawSys.cam.scale;
	drawSys.frames.push_back(frame);

}

Control::~Control() {

}

Vector2d Control::getCursorPos() {
	return geom::rotate((mouse.pos - drawSys.cam.border/2) / drawSys.cam.scale, drawSys.cam.angle);
}

void Control::loadConfig() {
	
}


void Control::saveConfig() {
	
}

std::string Control::randomName(int n) {
	std::string symbols = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
	std::string name = "";
	for (int i = 0; i < n; i++) {
		name += symbols[random::intRandom(0, symbols.size() - 1)];
	}
	return name;
}

void Control::step() {
	//dt = 0.05;
	int timeMs = getMilliCount();
	if (timeMs - timePrev > dt) {
		timePrev = timeMs;
		
		
		events();
		drawSys.mouse = mouse;
		Camera& cam = drawSys.cam;
		long double camVel = 100/cam.scale;
		int state = 0;

		if (keys[LEFT]) {
			drawSys.valueConst += 0.002;
			drawSys.setImage(1, 0);
		}
		if (keys[RIGHT]) {
			drawSys.valueConst -= 0.002;
			drawSys.setImage(1, 0);
		}
		if (keys[UP]) {
			drawSys.valueK *= 1.02;
			drawSys.setImage(1, 0);
		}
		if (keys[DOWN]) {
			drawSys.valueK /= 1.02;
			drawSys.setImage(1, 0);
		}
		if (keys[C]) {
			drawSys.colorConst += 10;
			drawSys.setImage(1, 0);
		}
		if (keys[P]) {
			Frame frame;
			frame.image = drawSys.img;
			frame.pos = drawSys.cam.pos;
			frame.scale = drawSys.cam.scale;
			frame.values = drawSys.values;
			drawSys.frames.push_back(frame);
			//
			double k = config.photoQuality;
			cam.scale *= k;
			drawSys.createFractal(Vector2d(drawSys.w * k, drawSys.h * k), config.photoIterations, 1);
			sf::Image img = drawSys.makeImage(Vector2d(drawSys.w*k, drawSys.h*k), config.photoIterations, 1);
			cam.scale /= k;
			img.saveToFile("pictures/" + randomName(8) + ".png");
			//
			drawSys.cam.pos = drawSys.frames.back().pos;
			drawSys.cam.scale = drawSys.frames.back().scale;
			drawSys.img = drawSys.frames.back().image;
			drawSys.draw();
			drawSys.values = drawSys.frames.back().values;

			drawSys.frames.pop_back();
		}
		if (mouse.state) {
			//saving frame
			Frame frame;
			frame.image = drawSys.img;
			frame.pos = drawSys.cam.pos;
			frame.scale = drawSys.cam.scale;
			frame.values = drawSys.values;
			drawSys.frames.push_back(frame);
			//configuring fractal
			long double dS = drawSys.zoom;
			cam.border = Vector2d(drawSys.w, drawSys.h);
			cam.pos += (mouse.pos - cam.border / 2) / cam.scale;
			drawSys.cam.scale *= dS;
			state = 1;
		}
		if (keys[ESCAPE] && !keysPrev[ESCAPE]) {
			if (drawSys.frames.size() > 0) {
				drawSys.cam.pos = drawSys.frames.back().pos;
				drawSys.cam.scale = drawSys.frames.back().scale;
				drawSys.img = drawSys.frames.back().image;
				drawSys.draw();
				drawSys.values = drawSys.frames.back().values;
				
				drawSys.frames.pop_back();
			}
		}
		
		if (state) {
			drawSys.system = &sys;
			drawSys.setImage(1, 1);
			
		}
		drawSys.zoom *= pow(1.1, mouse.delta);
		drawSys.draw();
		drawSys.window->display();
			
	}
}
