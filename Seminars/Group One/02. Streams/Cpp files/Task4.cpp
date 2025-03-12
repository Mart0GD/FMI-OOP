#include <iostream>
#include <fstream>

#define MAX_FILE_NAME 128
#define BUFFER 1024
/*
Напишете програма, която работи подобно на програмата от задача 2, но се очаква
файловете да са от цели числа, разделени с интервал. Проверете дали всеки от тях е
сортиран в нарастващ ред (според задача 3) и след това ги слейте в резултатния файл,
така че той да съдържа всички числа от всички файлове в сортиран вид (сортирано
сливане на сортирани файлове). За разделител използвайте интервал.
*/

void freeMatrix(char** matrix, size_t size);
char** createMatrix(size_t rows, size_t cols);
void readFiles(int filesCount, char** fileNames);
bool validateFiles(char** files, size_t cnt);
void fromConsole(char* fileName);
void copyToFile(const char* from, const char* to);
void copyAndSortAll(char** fileNames, size_t filesCount);
bool contains(int* arr, int element, size_t size);
void sort(int* numbers, size_t size);

int main4() {
	int filesCount = 0;
	std::cout << "Enter files count --> ";
	std::cin >> filesCount;

	char** fileNames = createMatrix(filesCount, MAX_FILE_NAME);
	if (!fileNames) return -1;

	std::cin.ignore();
	readFiles(filesCount, fileNames);
	
	bool res;
	switch (filesCount)
	{
		case 1:
			fromConsole(fileNames[0]);
		break;

		case 2:
			res = validateFiles(fileNames, filesCount - 1);
			if (!res) return -1;
			
			copyToFile(fileNames[0], fileNames[1]);
		break;

		default:
			res = validateFiles(fileNames, filesCount - 1);
			if (!res) return -1;

			copyAndSortAll(fileNames, filesCount);
		break;
	}

	freeMatrix(fileNames, filesCount);
	return 0;
}

void readFiles(int filesCount, char** fileNames){
	for (int i = 0; i < filesCount; i++) {
		std::cout << "Enter file name --> ";
		std::cin.getline(fileNames[i], MAX_FILE_NAME);
		if(i + 1 < filesCount) std::cout << '\n';
	}
}

bool validateFiles(char** files, size_t cnt) {
	std::ifstream file;
	for (int i = 0; i < cnt; i++){
		file.open(files[i]);
		if (!file.is_open()) {
			std::cerr << "Cannot open file!";
			return false;
		}

		int number = 0;
		int lastNumber = INT_MIN;
		while (!file.eof()){
			file >> number;
			if (!file || number <= lastNumber) return false;
			lastNumber = number;
		}
		file.close();
	}
}

void fromConsole(char* fileName) {
	if (!fileName) return;

	std::ofstream file(fileName, std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Cannot open file!";
		return;
	}

	int* numbers = new(std::nothrow) int[1024];
	if (!numbers) return;

	std::cout << "Enter numbers --> ";

	int number = 0;
	int lastNumber = INT_MIN;
	bool valid = true;
	int numbersCnt = 0;
	do
	{
		std::cin >> number;
		if (number <= lastNumber) {
			valid = false;
			break;
		}
		lastNumber = number;
		numbers[numbersCnt++] = number;
	} while (std::cin.get() != '\n');

	if (valid)
	{
		for (int i = 0; i < numbersCnt; i++) {
			file << numbers[i] << ' ';
		}
	}

	delete[] numbers;
	file.close();
}

void copyToFile(const char* from, const char* to) {
	std::ifstream input(from);
	std::ofstream output(to, std::ios::in);

	if (!input.is_open() || output.is_open()){
		std::cerr << "Cannot open file!";
		return;
	}

	int number = 0;
	while (!input.eof()){
		input >> number;
		output << number << ' ';
	}

	input.close();
	output.close();
}

bool contains(int* arr, int element, size_t size) {
	for (int i = 0; i < size; i++){
		if (element == arr[i]) return true;
	}

	return false;
}

void sort(int* numbers, size_t size) {
	bool swapped = false;
	int temp = 0;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size - 1 - i; j++){
			if (numbers[j] < numbers[j + 1]) continue;

			temp = numbers[j];
			numbers[j] = numbers[j + 1];
			numbers[j + 1] = temp;
			swapped = true;
		}
		if (!swapped) break;
	}
}

void copyAndSortAll(char** fileNames, size_t filesCount) {
	int* numbers = new(std::nothrow) int[BUFFER];
	if (!numbers) return;

	int cnt = 0;
	std::ifstream file;
	for (int i = 0; i < filesCount - 1; i++){
		file.open(fileNames[i]);
		if (!file.is_open()) {
			std::cerr << "Cannot open file!";
		}

		int number = 0;
		while (!file.eof()){
			file >> number;
			if (!contains(numbers, number, cnt)) numbers[cnt++] = number;
		}
		file.close();
	}

	sort(numbers, cnt);
	std::ofstream output(fileNames[filesCount - 1]);
	if (!output.is_open()){
		std::cerr << "Cannot open file!";
		delete[] numbers;
		return;
	}

	for (int i = 0; i < cnt; i++){
		output << numbers[i];
		if (i + 1 < cnt) output << ' ';
	}
	output.close();
	delete[] numbers;
}

void freeMatrix(char** matrix, size_t size) {

	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;
}

char** createMatrix(size_t rows, size_t cols) {
	char** matrix = new(std::nothrow) char* [rows];
	if (!matrix) return NULL;

	for (int i = 0; i < rows; i++) {
		matrix[i] = new(std::nothrow) char[cols];
		if (!matrix[i]) {
			freeMatrix(matrix, i);
		}
	}

	return matrix;
}