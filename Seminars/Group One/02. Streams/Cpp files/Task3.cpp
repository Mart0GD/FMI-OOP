#include <iostream>
#include <fstream>

#define MAX_FILE_NAME 64
/*
Напишете програма, която прочита от стандартния вход име на текстов файл. Той трябва
да е съставен от цели числа, разделени с един или повече празни символи. Целта е да
се проверят две условия: 1) дали файлът е с коректен формат и 2) дали числата в него
са подредени в нарастващ ред.
*/

int main3() {

	char* fileName = new(std::nothrow) char[MAX_FILE_NAME];
	if (!fileName) return 1;

	std::cout << "Enter file name --> ";
	std::cin >> fileName;

	std::ifstream input(fileName);
	if (!input.is_open()) {
		std::cerr << "Cannot open file!";
		return 1;
	}

	bool valid = true;
	char c = ' ';
	int number = 0;
	int lastNumber = INT_MIN;

	while (!input.eof() && valid){
		input >> number;
		if (!input || number <= lastNumber) valid = false;
		lastNumber = number;
	}

	std::cout << std::boolalpha;
	std::cout << "Is file valid --> " << valid;


	delete[] fileName;
	input.close();
	return valid;
}
