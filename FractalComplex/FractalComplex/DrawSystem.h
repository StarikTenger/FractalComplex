#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Color.h"
#include "System.h"
#include "Camera.h"
#include "Mouse.h"
#include "Config.h"

class DrawSystem {
public:
	sf::RenderWindow* window;
	Camera cam;
	System* system;
	bool fullscreenMode = 0;
	DrawSystem();
	~DrawSystem();
	Mouse mouse;
	long double w, h;
	long double blockSize = 1;
	long double zoom = 2;
	sf::Image img;
	int mode = 0;

	Config* config;

	void draw();
	void drawScene();
	void drawInterface();
	void setImage();
	sf::Image makeImage(Vector2d box, int iterations);
	sf::Font font;
	
//private:
	//basics

	Color fromHSV(long double H, long double S, long double V);
	void fillRect(long double x, long double y, long double width, long double height, Color color);
	void strokeRect(long double x, long double y, long double width, long double height, Color color);
	void image(std::string name, long double x, long double y, long double width, long double height, long double angle);
	void image(std::string name, long double x, long double y, long double width, long double height, long double angle, Color color);
	void image(std::string name, long double x, long double y, long double width, long double height, long double angle, long double d);
	void text(std::string text, long double x, long double y, int size, Color color);
	//objects
	
	//load
	std::map<std::string, sf::Texture*> textures;
	void loadTexture(std::string name, std::string path);
	void loadTextures();
};

