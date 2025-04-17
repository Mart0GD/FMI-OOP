#include "ISBN.hpp"

#pragma warning(disable: 4996)

ISBN::ISBN() 
	:ISBN("987-0-00-000000-0") 
{ }
ISBN::ISBN(const char* numbers) {
	if (!numbers || !*numbers) throw std::invalid_argument("Inavlid ISBN!");

	char symbols[ISBN_SIZE];

	char* buff;
	buff = readString(numbers);
	if (strcmp(buff, (char*)START_NUMBERS)) throw std::invalid_argument("Wrong ISBN format!");
	strcpy(symbols, buff);

	buff = readString(numbers);
	if(strlen(buff) != 1) throw std::invalid_argument("Wrong ISBN format!");
	strcpy(symbols + strlen(symbols), buff);


	buff = readString(numbers);
	if (strlen(buff) != 2) throw std::invalid_argument("Wrong ISBN format!");
	strcpy(symbols + strlen(symbols), buff);


	buff = readString(numbers);
	if (strlen(buff) != 6) throw std::invalid_argument("Wrong ISBN format!");
	strcpy(symbols + strlen(symbols), buff);


	buff = readString(numbers);
	if (strlen(buff) != 1) throw std::invalid_argument("Wrong ISBN format!");
	strcpy(symbols + strlen(symbols), buff);

	strcpy(this->numbers, symbols);
}

char* ISBN::readString(const char*& what) {
	static char buff[16];
	if (!what) buff;

	int iter = 0;
	while (*what != '-' && *what){
		buff[iter++] = *what;
		what++;
	}
	what++;
	buff[iter] = '\0';

	return buff;
}

const char ISBN::START_NUMBERS[] = "987";