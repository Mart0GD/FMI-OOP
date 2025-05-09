#include <iostream>
#include <fstream>
#include "Person.hpp"

#pragma warning(disable: 4996)

constexpr std::size_t nameSize{ 128 };

bool createPerson(Person& person, int argc, char* args[]) {
	if (argc != 6 || !args[2] || !args[3]) return false;


	person.name = new(std::nothrow) char[strlen(args[2]) + 1];
	if (!person.name) return false;

	person.lastName = new(std::nothrow) char[strlen(args[3]) + 1];
	if (!person.name) return false;

	strcpy(person.name, args[2]);
	strcpy(person.lastName, args[3]);
	person.age = atoi(args[4]);
	person.weight = atof(args[5]);

	return true;
}

void printPerson(Person& person) {
	std::cerr
		<< person.name << ' '
		<< person.lastName << ' '
		<< person.age << ' '
		<< person.weight;
}

bool write(const Person& person, const char* fileName) {
	std::ofstream file(fileName, std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Cannot open binary file to write!";
		return false;
	}

	size_t firstNameSize = strlen(person.name) + 1;
	file.write(reinterpret_cast<const char*>(&firstNameSize), sizeof(firstNameSize));
	file.write(reinterpret_cast<const char*>(person.name), firstNameSize);


	size_t lastNameSize = strlen(person.lastName) + 1;
	file.write(reinterpret_cast<const char*>(&lastNameSize), sizeof(lastNameSize));
	file.write(reinterpret_cast<const char*>(person.lastName), lastNameSize);

	file.write(reinterpret_cast<const char*>(&person.age), sizeof(person.age));
	file.write(reinterpret_cast<const char*>(&person.weight), sizeof(person.weight));

	file.close();
	return true;
}

bool read(Person& person, const char* fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Cannot open binary file to write!";
		return false;
	}
	free(person);

	size_t firstNameSize{};
	file.read(reinterpret_cast<char*>(&firstNameSize), sizeof(firstNameSize));

	person.name = new(std::nothrow) char[firstNameSize];
	if (!person.name) return false;
	file.read(reinterpret_cast<char*>(person.name), firstNameSize);


	size_t lastNameSize{};
	file.read(reinterpret_cast<char*>(&lastNameSize), sizeof(lastNameSize));

	person.lastName = new(std::nothrow) char[lastNameSize];
	if (!person.lastName) {
		free(person);
		return false;
	}
	file.read(reinterpret_cast<char*>(person.lastName), lastNameSize);

	file.read(reinterpret_cast<char*>(&person.age), sizeof(person.age));
	file.read(reinterpret_cast<char*>(&person.weight), sizeof(person.weight));

	file.close();
	return true;
}

void free(Person& person) {
	if(person.name) delete[] person.name;
	if(person.lastName) delete[] person.lastName;

	person.name = nullptr;
	person.lastName = nullptr;
}

int parse(char* str) {

	return 1;
}

float_t fparse(char* str) {

	return 1.0;
}