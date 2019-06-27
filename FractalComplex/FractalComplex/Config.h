#pragma once
#include <string>

class Config {
public:
	int iterations = 1000;

	double periodH = 245;
	double frequencyH = 5;
	double amplitudeH = 1;

	double periodS = 0.5;
	double frequencyS = 0;
	double amplitudeS = 1;

	double periodV = 0.5;
	double frequencyV = 0;
	double amplitudeV = 1;

	Config();
	Config(std::string path);
	~Config();
	
};

