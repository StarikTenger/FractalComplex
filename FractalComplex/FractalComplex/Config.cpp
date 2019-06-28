#include "Config.h"
#include <iostream>
#include <fstream>

Config::Config() {

}

Config::Config(std::string path) {
	std::ifstream file(path);
	while (file) {
		std::string param;
		file >> param;
		if (param == "END") {
			break;
		}
		if (param == "ITERATIONS") {
			file >> iterations;
		}
		//////////////
		if (param == "H_PERIOD") {
			file >> periodH;
		}
		if (param == "H_FREQUENCY") {
			file >> frequencyH;
		}
		if (param == "H_AMPLITUDE") {
			file >> amplitudeH;
		}
		//////////////
		if (param == "S_PERIOD") {
			file >> periodS;
		}
		if (param == "S_FREQUENCY") {
			file >> frequencyS;
		}
		if (param == "S_AMPLITUDE") {
			file >> amplitudeS;
		}
		if (param == "S_CONSTANT") {
			file >> constantS;
		}
		//////////////
		if (param == "V_PERIOD") {
			file >> periodV;
		}
		if (param == "V_FREQUENCY") {
			file >> frequencyV;
		}
		if (param == "V_AMPLITUDE") {
			file >> amplitudeV;
		}
		if (param == "V_CONSTANT") {
			file >> constantV;
		}
		//////////////
		if (param == "PHOTO_QUALITY") {
			file >> photoQuality;
		}
		if (param == "PHOTO_ITERATIONS") {
			file >> photoIterations;
		}
	}
}

Config::~Config() {
	
}