#include <iostream>
#include <cstring>
#include "../Headers/Address.hpp"
#include "../Headers/Helpers.hpp"

#define MAX_ADDRESS_LEN 1024
#pragma warning(disable : 4996)
/*
struct Address {
	char town[MAX_TOWN_LEN];
	unsigned postalCode;
	char street[MAX_STREET_LEN];
	unsigned streetNumber;
	char streetLetter;
	unsigned short entrance;
	unsigned short floor;
	unsigned short apt;
};
"Sofia", 1234, "tsar Simeon street", 10 a, ent. 2, fl. 7, apt. 30.
*/

void ReadAddress(Address& address) { 
	char town[MAX_TOWN_LEN] = {};
	unsigned postalCode;
	char street[MAX_STREET_LEN] = {};
	unsigned streetNum = 0;
	char streetLetter = ' ';
	int entrance;
	int floor;
	int apt;


	std::cin.getline(town, MAX_TOWN_LEN, ',');
	std::cin >> postalCode;
	std::cin.ignore();
	std::cin.getline(street, MAX_STREET_LEN, ',');
	std::cin >> streetNum;
	std::cin >> streetLetter;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '.');
	std::cin >> entrance;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '.');
	std::cin >> floor;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '.');
	std::cin >> apt;

	strcpy(address.town, town);
	address.postalCode = postalCode;
	strcpy(address.street, street);
	address.streetNumber = streetNum;
	address.streetLetter = streetLetter;
	address.entrance = entrance;
	address.floor = floor;
	address.apt = apt;
}

void RandomAddress(Address& address) {
	srand(std::time(nullptr));

	strcpy(address.town, generateRandomText(rand() % MAX_TOWN_LEN));
	address.postalCode = rand() % 9999;
	strcpy(address.street, generateRandomText(rand() % MAX_STREET_LEN));
	address.streetNumber = rand() % 9;
	address.streetLetter = rand() % 25 + 'a';
	address.entrance = rand() % 5;
	address.floor = rand() % 12;
	address.apt = rand() % 3;
}

void PrintAddress(const Address& address) {

	std::cout
		<< address.town
		<< ", "
		<< address.postalCode
		<< ","
		<< address.street
		<< ", "
		<< address.streetNumber
		<< ' '
		<< address.streetLetter
		<< ", ent. "
		<< address.entrance
		<< ", fl. "
		<< address.floor
		<< ", apt. "
		<< address.apt
		<< '.'
		<< std::endl;
}