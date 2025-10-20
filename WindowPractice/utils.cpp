#include <string>
#include <fstream>
#include <sstream>
#include"utils.h"

std::string LoadShaderSource(const char* filepath) {
	std::ifstream file(filepath);

	if (!file.is_open()) {
		std::cerr << "Failed to open shader file: " << filepath << std::endl;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}