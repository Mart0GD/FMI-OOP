#pragma once
#ifndef HELPER_HPP
#define HELPER_HPP

#include <fstream>


inline void revert(std::istream& file) {
	file.clear();
	file.seekg(0, std::ios::beg);
}

inline int getLinesCount(std::istream& file) {

	int rows = 0;
	while (file) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (!file) break;
		rows++;
	}

	revert(file);
	return rows;
}
#endif