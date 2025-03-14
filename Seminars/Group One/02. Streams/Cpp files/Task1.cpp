#include <iostream>
#include <fstream>
#define MAX_FILE_NAME 64
/*
������ 1.
4 �������� ��������, ����� �������� �� ��������� ��� ��� ���������� - ������� � �������
- ���� ��: -c, -C , -w, -l, -L, -s ��� -h. ������� � ��� �� ����.
5 ���������� ������ �� ��������� ��������� ���� � ������� ����� ������ ��������� � ��
������ ���������� ��������� ��:
6 -c -> ���� �� ��������� ��� ����� (������ �������).
7 -C -> ���� �� ��-�������� ������� ��� ����� - ������� � ��� ��-����� �� 32 � ��-�����
�� 127.
8 -w -> ���� �� ������ ��� �����. ������ �� �������� � ���������� ���� ������ �������.
9 -l -> ���� �� �������� ��� �����.
10 -L -> ���� �� ��-�������� ������ ��� �����. �� ������ �� �������� ���� ���� ������
(��� �������� �����).
11 -s -> ������� ���������� �� �����. �� ������� ����� �� ������� �������, �� ���� �
����� �������� �� ����� ���� ������� � ��������� �� ����� �������� ������.
12 -h -> ������� ������� ��������� �� ������ (help message). �� �������� ������
���������.
*/

int getFileLength(std::ifstream& file);
int getNWSCharactersCount(std::ifstream& file);
void PrintWordsCount(std::ifstream& file);
void PrintRowsCount(std::ifstream& file);
void PrintNonEmptyRowsCount(std::ifstream& file);
void PrintStatistic(std::ifstream& file);
void PrintHelpMenu();
void revert(std::istream& stream);

int main1() {

	char command;
	char* fileName = new(std::nothrow) char[MAX_FILE_NAME];
	if (!fileName) return -1;

	std::cout << "Enter command --> ";

	char ch;
	std::cin >> ch >> command;
	if (!std::cin || ch != '-') {
		std::cerr << "Invalid input!";
		return -1;
	}

	std::ifstream file;
	std::cout << "Enter file name --> ";
	std::cin.ignore();
	do
	{
		std::cin.getline(fileName, MAX_FILE_NAME);

		file.open(fileName);
		if (!file.is_open()) {
			std::cout << "File cannot be opened!\n";
		} else break;
	} while (true);
	
	bool done = true;
	do
	{
		switch (command)
		{
			case 'c':
				std::cout << "File length --> " << getFileLength(file) << std::endl;
				done = true;
			break;

			case 'C':
				std::cout << "NWS Characters --> " << getNWSCharactersCount(file) << std::endl;
				done = true;
			break;

			case 'w':
				PrintWordsCount(file);
				done = true;
			break;

			case 'l':
				PrintRowsCount(file);
				done = true;
			break;

			case 'L':
				PrintNonEmptyRowsCount(file);
				done = true;
			break;

			case 's':
				PrintStatistic(file);
				done = false;
			break;

			case 'h':
				PrintHelpMenu();
				done = false;
			break;
			
		}

		if (!done) {
			command = '\0';
			do
			{
				std::cin >> ch >> command;
			} while (ch != '-' && !command);
		}
	} while (!done);

	delete[] fileName;
	file.close();
	return 0;
}

bool IsWhiteSpace(char chr) {
	return !(chr > 32 && chr < 127);
}

int getFileLength(std::ifstream& file) {
	file.clear();
	file.seekg(0, std::ios::end);

	return file.tellg();
}

int getNWSCharactersCount(std::ifstream& file) {
	revert(file);

	int cnt = 0;
	while (!file.eof())
		if (!IsWhiteSpace(file.get())) cnt++;

	return cnt;
}

void PrintWordsCount(std::ifstream& file) {
	revert(file);

	int cnt = 0;
	bool wordStarted = false;
	char c = ' ';
	while (!file.eof()){
		c = file.get();

		if (wordStarted && IsWhiteSpace(c)){
			wordStarted = false;
			cnt++;
		}
		else if (!wordStarted && !IsWhiteSpace(c)) {
			wordStarted = true;
		}
	}
	if (wordStarted) cnt++;

	std::cout << "Words count --> " << cnt << std::endl;;
}

void PrintRowsCount(std::ifstream& file)  {
	revert(file);

	int rows = 0;
	char ch = '\0';
	while (!file.eof()){
		file.get(ch);
		if (ch == '\n') rows++;
	}
	if(ch) rows++;

	std::cout << "Rows count " << rows << std::endl;;
}

void PrintNonEmptyRowsCount(std::ifstream& file) {
	revert(file);

	int rows = 0;
	int characters = 0;
	char c = ' ';
	while (file.peek() != EOF){
		c = file.get();
		if (c == '\n' && characters > 0){
			characters = 0;
			rows++;
			continue;
		}
		if(!IsWhiteSpace(c))characters++;
	}
	if (characters > 0) rows++;
	
	std::cout << "Non empty rows --> " << rows << std::endl;;
}

void PrintStatistic(std::ifstream& file) {
	double allCharacters = getFileLength(file);

	double nws = getNWSCharactersCount(file);

	PrintWordsCount(file);

	PrintRowsCount(file);
	
	PrintNonEmptyRowsCount(file);

	std::cout << "NWS Characters perecentage --> " << (nws / allCharacters) * 100.0 << std::endl;
}

void PrintHelpMenu() {
	std::cout
		<< "-c --> All symbols in file\n"
		<< "-C --> All NWS symbols in file\n"
		<< "-w --> All words in file\n"
		<< "-l --> All rows in file\n"
		<< "-L --> All non empty rows in file\n"
		<< "-s --> Statistics\n"
		<< "-h --> Help!\n";
}

void revert(std::istream& stream) {
	stream.clear();
	stream.seekg(0, std::ios::beg);
}

