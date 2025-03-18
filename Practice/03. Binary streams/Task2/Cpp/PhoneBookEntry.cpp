#include <iostream>
#include <fstream>
#include "PhoneBookEntry.hpp"

#pragma warning(disable: 4996)

/*
char name[MAX_NAME_LEN]{};
char lastName[MAX_NAME_LEN]{};
char city[MAX_CITY_NAME_LEN]{};
char phoneNumber[MAX_PHONE_NUM_LEN]{};

*/


void readString(char* str, size_t size) {
	do
	{
		std::cin.getline(str, size, ' ');
	} while (!str[0]);
}

bool readEntry(PhoneBookEntry& phe) {
	char nameBuff[MAX_NAME_LEN] = {};
	readString(nameBuff, sizeof(nameBuff) / sizeof(nameBuff[0]));

	char lastNameBuff[MAX_NAME_LEN] = {};
	readString(lastNameBuff, sizeof(lastNameBuff) / sizeof(lastNameBuff[0]));

	char cityNameBuff[MAX_CITY_NAME_LEN] = {};
	readString(cityNameBuff, sizeof(cityNameBuff) / sizeof(cityNameBuff[0]));

	char phoneNumberBuff[MAX_PHONE_NUM_LEN] = {};
	readString(phoneNumberBuff, sizeof(phoneNumberBuff) / sizeof(phoneNumberBuff[0]));

	if (strlen(phoneNumberBuff) != 10) return false;

	strcpy(phe.name, nameBuff);
	strcpy(phe.lastName, lastNameBuff);
	strcpy(phe.city, cityNameBuff);
	strcpy(phe.phoneNumber, phoneNumberBuff);
	return true;
}

bool writeToFile(const char* fileName){
	std::ofstream file(fileName, std::ios::in | std::ios::binary | std::ios::app);
	if (!file.is_open()) {
		std::cerr << "Cannot open file for writing!";
		return false;
	}
	
	PhoneBookEntry entry = {};
	readEntry(entry);
	file.write(reinterpret_cast<const char*>(&entry), sizeof(entry));
	if (!file) return false;

	file.close();
	std::cout << "Adding entry was successful!";
	return true;
}

bool getEntryByKey(const char* fileName, PhoneBookEntry& phe) {
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Cannot open file for reading!";
		return false;
	}

	std::cout << "Enter key for search -c(city) -n(name) -f(family) -nf(name + family) --> ";

	char ch; char command[3] = {};
	std::cin >> ch; std::cin.getline(command, 3);
	if (!std::cin || !command[0]) return false;

	int buffer = 64;
	PhoneBookEntry* entries = new(std::nothrow) PhoneBookEntry[buffer];
	if (!entries) return false;

	PhoneBookEntry temp = {};
	int iter = 0;
	while (file.read(reinterpret_cast<char*>(&temp), sizeof(temp))){
		entries[iter++] = temp;
	} 

	bool found = false;
	if (strcmp(command, "c") == 0)
	{
		char* city = new(std::nothrow) char[MAX_CITY_NAME_LEN];
		if (!city) return -1;
		std::cout << "Enter city --> ";

		std::cin.getline(city, MAX_CITY_NAME_LEN);
		for (int i = 0; i < iter; i++) {
			if (strcmp(entries[i].city, city) == 0) {
				std::cout << "Number found!" << std::endl;
				printEntry(entries[i]);
				found = true;
				break;
			}

		}
		if (!found) std::cout << "No city matches the critiria";
	}
	else if (strcmp(command, "n") == 0) {
		char* name = new(std::nothrow) char[MAX_NAME_LEN];
		if (!name) return -1;
		std::cout << "Enter name --> ";

		std::cin.getline(name, MAX_CITY_NAME_LEN);
		for (int i = 0; i < iter; i++) {
			if (strcmp(entries[i].name, name) == 0) {
				std::cout << "Number found!" << std::endl;
				printEntry(entries[i]);
				found = true;
				break;
			}
		}
		if (!found) std::cout << "No name matches the critiria";
	}
	else if (strcmp(command, "f") == 0) {
		char* lName = new(std::nothrow) char[MAX_NAME_LEN];
		if (!lName) return -1;
		std::cout << "Enter last name --> ";

		std::cin.getline(lName, MAX_CITY_NAME_LEN);
		for (int i = 0; i < iter; i++) {
			if (strcmp(entries[i].lastName, lName) == 0) {
				std::cout << "Number found!" << std::endl;
				printEntry(entries[i]);
				found = true;
				break;
			}
		}
		if (!found) std::cout << "No last name matches the critiria!";
	}
	else if (strcmp(command, "nf") == 0) {
		char* name = new(std::nothrow) char[MAX_NAME_LEN];
		if (!name) return -1;

		char* lName = new(std::nothrow) char[MAX_NAME_LEN];
		if (!lName) return -1;

		std::cout << "Enter name --> ";
		std::cin.getline(name, MAX_CITY_NAME_LEN);

		std::cout << "Enter last name --> ";
		std::cin.getline(lName, MAX_CITY_NAME_LEN);

		for (int i = 0; i < iter; i++) {
			if (strcmp(entries[i].name, name) == 0 && strcmp(entries[i].lastName, lName) == 0) {
				std::cout << "Number found!" << std::endl;
				printEntry(entries[i]);
				found = true;
				break;
			}
		}
		if (!found) std::cout << "No name and last name like this matches the critiria!";
	}
	else {
		std::cerr << "Error... Unkown command!";
	}

	delete[] entries;
}

void printEntry(const PhoneBookEntry& phe) {
	std::cout
		<< phe.name << ' '
		<< phe.lastName << ' '
		<< phe.city << ' '
		<< phe.phoneNumber << ' ';
}