#pragma once
#include <string>

class Config {
public:
	int iterations = 1000;

	long double periodH = 245;
	long double frequencyH = 5;
	long double amplitudeH = 1;

	long double periodS = 0.5;
	long double frequencyS = 0;
	long double amplitudeS = 1;
	long double constantS = 0;

	long double periodV = 0.5;
	long double frequencyV = 0;
	long double amplitudeV = 1;
	long double constantV = 0;

	long double photoQuality = 1;
	int photoIterations = iterations;

	Config();
	Config(std::string path);
	~Config();
	
};

