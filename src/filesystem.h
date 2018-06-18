#pragma once
#include <string>
#include <fstream>

std::string loadFileAsString(std::string filename) {
	std::ifstream ifs(filename);
	if(ifs.is_open() ) {
		std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		return str;
	}
	else return "";
}