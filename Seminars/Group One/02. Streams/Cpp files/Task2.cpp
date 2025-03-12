#include<iostream>
#include<fstream>

#define MAX_FILE_LETTERS_COUNT 128
#define END_KEYWORD "/break"
#define READ_BUFFER 1028
/*
Напишете програма, която получава от командния ред положителен брой параметри - имена
на файлове. Целта е да се слее съдържанието на всички файлове (без последния) във
файл с име последния аргумент. Съдържанието на файловете се записва последователно -
първо първия файл, след това втория и т.н.
Ако е подаден само един аргумент - за входен файл се използва стандартният вход и
каквото се въведе от него се записва в резултатния файл. Ако са подадени две имена на
файлове, програмата трябва да копира първия файл във втория. Работете с файловете в
текстов режим.
*/

char** CreateMatrix(size_t rows, size_t cols);
void free(char** matrix, size_t size);
bool PrintFromConsole(char* fileName);
bool CopyToFile(char* from, char* to);
bool CopyToLast(char** files, size_t filesCount);

int main2() {
	int filesCount = 0;
	std::cout << "Insert files count --> ";
	std::cin >> filesCount;

	char** fileNames = CreateMatrix(filesCount, MAX_FILE_LETTERS_COUNT);
	if (!fileNames) return 1;

	std::cin.ignore();
	for (int i = 0; i < filesCount; i++){
		std::cout << "File " << i + 1 << ". --> ";
		std::cin.getline(fileNames[i], MAX_FILE_LETTERS_COUNT);
	}

	switch (filesCount)
	{
		case 1:
			PrintFromConsole(fileNames[0]);
		break;

		case 2:
			CopyToFile(fileNames[0], fileNames[1]);
		break;

		default:
			CopyToLast(fileNames, filesCount);
		break;
	}

	free(fileNames, filesCount);
	return 0;
}

void free(char** matrix, size_t size) {
	for (size_t i = 0; i < size; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}

	delete[] matrix;
	matrix = nullptr;
}

char** CreateMatrix(size_t rows, size_t cols) {
	char** matrix = new(std::nothrow) char* [rows];
	if (!matrix) return NULL;

	for (int i = 0; i < rows; i++) {
		matrix[i] = new(std::nothrow) char[cols];
		if (!matrix[i]) {
			free(matrix, i);
			return NULL;
		}
	}

	return matrix;
}

bool PrintFromConsole(char* fileName) {
	std::ofstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Cannot open file!";
		return false;
	}

	std::cout << "Enter text to put in file (end with /break) --> " << std::endl;
	char* currentLine = new(std::nothrow) char[READ_BUFFER];
	if (!currentLine) return false;

	do
	{
		std::cin.getline(currentLine, READ_BUFFER);
		if (!currentLine) continue;
		else if (strcmp(currentLine, END_KEYWORD) == 0) break;

		file << currentLine;
		file << '\n';
	} while (true);

	file.close();
	delete[] currentLine;
	return true;
}

bool CopyToFile(char* from, char* to) {
	std::ifstream input(from);
	std::ofstream output(to);

	if (!input.is_open() || !output.is_open()) {
		std::cerr << "Cannot open file!";
		return false;
	}

	char* buffer = new(std::nothrow) char[READ_BUFFER];
	if (!buffer) return false;

	while (!input.eof()){
		input.getline(buffer, READ_BUFFER);
		output << buffer << '\n';
	}

	input.close();
	output.close();
	delete[] buffer;
	return true;
}

bool CopyToLast(char** files, size_t filesCount) {
	
	std::ofstream output(files[filesCount - 1]);
	if (!output.is_open()) {
		std::cerr << "Cannot open file!" << std::endl;
		return false;
	}

	bool res = true;
	std::ifstream input;
	char* buffer = new(std::nothrow) char[READ_BUFFER];
	if (!buffer) return false;

	for (int i = 0; i < filesCount - 1; i++){
		input.open(files[i]);
		if (!input.is_open()) {
			std::cerr << "Cannot open file!" << std::endl;
			res = false;
			break;
		}

		while (!input.eof()){
			input.getline(buffer, READ_BUFFER);
			output << buffer << '\n';
		}
		input.close();
	}

	output.close();
	delete[] buffer;
	return res;
}
