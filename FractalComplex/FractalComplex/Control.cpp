#include "Control.h"
#include "getMilliCount.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
	drawSys.setImage();

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

void Control::step() {
	//dt = 0.05;
	int timeMs = getMilliCount();
	if (timeMs - timePrev > dt) {
		timePrev = timeMs;
		
		
		events();
		drawSys.mouse = mouse;
		Camera& cam = drawSys.cam;
		double camVel = 100/cam.scale;
		int state = 0;

		if (keys[SPACE]) {
			cam.scale *= 2;
			state = 1;
		}
		if (keys[LEFT]) {
			cam.pos.x -= camVel;
			state = 1;
		}
		if (keys[RIGHT]) {
			cam.pos.x += camVel;
			state = 1;
		}
		if (keys[UP]) {
			cam.pos.y -= camVel;
			state = 1;
		}
		if (keys[DOWN]) {
			cam.pos.y += camVel;
			state = 1;
		}
		if (mouse.state) {
			double dS = drawSys.zoom;
			cam.border = Vector2d(drawSys.w, drawSys.h);
			cam.pos += (mouse.pos - cam.border / 2) / cam.scale;
			drawSys.cam.scale *= dS;
			//drawSys.cam.pos += (drawSys.cam.border / 2 - mouse.pos) / drawSys.cam.scale * (1 - dS); //it works
			state = 1;
		}
		if (state) {
			drawSys.system = &sys;
			drawSys.setImage();
			
		}
		drawSys.zoom *= pow(1.1, mouse.delta);
		drawSys.draw();
		drawSys.window->display();
			
	}
}
