#pragma once
#include <iostream>
/*
Структура PhonebookEntry:

име -> низ с произволна дължина (не повече от 50)
фамилия -> низ с произволна дължина (не повече от 50)
град -> низ с произволна дължина (не повече от 50)
телефонен номер -> 10 цифри
*/

constexpr std::size_t MAX_NAME_LEN{ 50 };
constexpr std::size_t MAX_CITY_NAME_LEN{ 50 };
constexpr std::size_t MAX_PHONE_NUM_LEN{ 11 };

struct PhoneBookEntry {
	char name[MAX_NAME_LEN]{};
	char lastName[MAX_NAME_LEN]{};
	char city[MAX_CITY_NAME_LEN]{};
	char phoneNumber[MAX_PHONE_NUM_LEN]{};
};

bool readEntry(PhoneBookEntry& phe);
void printEntry(const PhoneBookEntry& phe);
bool writeToFile(const char* fileName);
bool getEntryByKey(const char* fileName, PhoneBookEntry& phe);