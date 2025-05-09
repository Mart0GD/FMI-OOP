#include <iostream>
#include <fstream>

#include "PhoneBookEntry.hpp"

#define FILE_NAME_CODE 1
#define MODE_CODE 2

#define FNAME_INDEX 0
#define LNAME_INDEX 1
#define CITY_INDEX 2
#define PHONE_NUMBER_INDEX 3
#define STEP 4

/*

Напишете програма, която получава като командни аргументи име на файл и режим на работа. Файла винаги ще е бинарен и ще пази информация за телефонен указател. Възможните режими на работа са следните:

write -> Записва номера в края на файла
read -> Дава възможност за търсене на номера по град, име, фамилия или име + фамилия. Като изписва нужната информация за един номер.
*/

int main2(int argc, char* args[]) {
	char* fileName = args[FILE_NAME_CODE];
	char* mode = args[MODE_CODE];

	bool isRead = strcmp(mode, "read") == 0;
	if (isRead) {
		PhoneBookEntry phe = {};
		getEntryByKey(fileName, phe);
	}
	else {
		std::cout << "Enter Phone entry to write in phonebook --> ";
		PhoneBookEntry phe = {};
		writeToFile(fileName);
	}

	return 0;
}