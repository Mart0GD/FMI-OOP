#pragma once

#include <iostream>

class ISBN {
public:
	ISBN();
	ISBN(const char* numbers);

	const char* getNumbers() const { return numbers; }

private:
	char* readString(const char*& what);

private:
	static const uint32_t ISBN_SIZE{14}; // +1 for \0
	static const char START_NUMBERS[];

	char numbers[ISBN_SIZE];
};