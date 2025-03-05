#pragma once
#include <iostream>

inline char* readInputString(size_t size) {
	char* buffer = new(std::nothrow) char[size];
	if (!buffer) return NULL;

	char c = ' ';
	do {
		if (std::cin.peek() == '\n') {
			std::cin.ignore();  
		}
		std::cin.getline(buffer, size);
	} while (!buffer);

	return buffer;
}