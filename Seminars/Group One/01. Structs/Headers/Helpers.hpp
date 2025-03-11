#ifndef HELPERS_H
#define HELPERS_H
#include <iostream>
#include <cstring>

inline char* ToString(long long number) {
	int digits = 1;
	long long temp = number;
	while (temp /= 10)
		digits++;

	char* str = new(std::nothrow) char[digits + 1];
	if (!str) return NULL;

	for (int i = digits; i >= 0; i--){
		str[i] = (number % 10) + '0';
		number /= 10;
	}
	str[digits + 1] = '\0';

	return str;
}

inline char* generateRandomText(size_t length) {
	const char* chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@";
	char* randomStr = new(std::nothrow) char[length];
	if (!randomStr) return NULL;

	srand(std::time(nullptr));
	for (size_t i = 0; i < length; ++i) {
		randomStr[i] = chars[std::rand() % strlen(chars)];
	}
	return randomStr;
}

#endif
