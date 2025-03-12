#include <iostream>
#include <fstream>
#include "Date.hpp"

#define BUFFER 1028
/*
Всеки ред на текстов файл съдържа две дати във формат dd-mm-yyyy или ddmm-yy, които
са разделени с един или повече интервали. Да се създаде нов текстов файл, всеки ред
на който съдържа цяло число, ако на съответния ред на входния файл има две коректно
записани дати и '*' в противен случай. Цялото число, съответстващо на коректните дати
да е равно на разликата в дни между първата и втората дата.
*/

int main8() {
	char* inputFileName = new(std::nothrow) char[BUFFER];
	if (!inputFileName) return 1;

	std::cout << "Enter input file --> ";
	std::cin.getline(inputFileName, BUFFER);

	char* outputFileName = new(std::nothrow) char[BUFFER];
	if (!outputFileName) return 1;

	std::cout << "Enter output file --> ";
	std::cin.getline(outputFileName, BUFFER);

	std::ifstream in(inputFileName);
	if (!in.is_open()) {
		std::cerr << "Cannot open file to read!";
		return 1;
	}

	std::ofstream out(outputFileName);
	if (!out.is_open()) {
		std::cerr << "Cannot open file to append!";
		return 1;
	}

	Date date1; Date date2;
	bool valid = true;
	while (!in.eof()){
		valid = readDate(date1, in);
		if (!valid) {
			in.ignore(1024, '\n');
			out << '*' << '\n';
			continue;
		}
		valid = readDate(date2, in);
		if (!valid) {
			in.ignore(1024, '\n');
			out << '*' << '\n';
			continue;
		}
		out << diff(date1, date2) << '\n';
	}

	delete[] inputFileName;
	delete[] outputFileName;
	in.close();
	out.close();
	return 0;
}