#pragma once
#include <iostream>
/*
��������� PhonebookEntry:

��� -> ��� � ���������� ������� (�� ������ �� 50)
������� -> ��� � ���������� ������� (�� ������ �� 50)
���� -> ��� � ���������� ������� (�� ������ �� 50)
��������� ����� -> 10 �����
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