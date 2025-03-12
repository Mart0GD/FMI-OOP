#pragma once
#ifndef HELPER_HPP
#define HELPER_HPP

#include <fstream>

inline int getLinesCount(const char* fileName, std::ifstream& file) {
	int lines = 0;
	char c = ' ';
	while (!file.eof()) {
		file.get(c);
		if (c == '\n') lines++;
	}
	file.clear();
	file.seekg(0, std::ios::beg);

	return lines + 1;
}

#endif