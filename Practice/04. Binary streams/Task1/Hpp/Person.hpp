#pragma once
#include <iostream>

/*
В програмата ще работим със структурата Person:

име -> низ с произволна дължина
фамилия -> низ с произволна дължина
години -> цяло число
тегло в килограми -> реално число
*/

struct Person {
	char* name{nullptr};
	char* lastName{nullptr};
	uint32_t age{};
	float_t weight{};
};

bool createPerson(Person& person, int argc, char* args[]);
void printPerson(Person& person);
bool read(Person& person, const char* fileName);
bool write(const Person& person, const char* fileName);

void free(Person& person);