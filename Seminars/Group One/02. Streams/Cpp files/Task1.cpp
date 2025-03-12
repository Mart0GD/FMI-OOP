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

void ClearWhitespace();
int PrintFileLength(std::ifstream& file);
int PrintNWSCCount(std::ifstream& file);
void PrintWordsCount(std::ifstream& file);
void PrintRowsCount(std::ifstream& file);
void PrintNonEmptyRowsCount(std::ifstream& file);
void PrintStatistic(std::ifstream& file);
void PrintHelpMenu();

int main() {

	char command;
	char* fileName = new(std::nothrow) char[MAX_FILE_NAME];
	if (!fileName) return 1;

	std::cin.ignore(1, '-');
	std::cin >> command;
	ClearWhitespace();
	std::ifstream file;

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
				PrintFileLength(file);
				done = true;
			break;

			case 'C':
				PrintNWSCCount(file);
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
			ClearWhitespace();
			std::cin.ignore(1, '-');
			std::cin >> command;
		}
	} while (!done);

	delete[] fileName;
	file.close();
	return 0;
}


void ClearWhitespace() {
	while (std::cin.peek() == ' ' || std::cin.peek() == '\n')
		std::cin.ignore();
}

bool IsWhiteSpace(char chr) {
	return !(chr > 32 && chr < 127);
}

int PrintFileLength(std::ifstream& file) {
	file.clear();
	file.seekg(0, std::ios::end);

	std::cout << "File length --> " << file.tellg() << std::endl;
	return file.tellg();
}

int PrintNWSCCount(std::ifstream& file) {
	file.clear();
	file.seekg(0, std::ios::beg);

	int cnt = 0;
	while (file.peek() != EOF){
		if (!IsWhiteSpace(file.get())) cnt++;
	}

	std::cout << "NWS Characters --> " << cnt << std::endl;
	return cnt;
}

void PrintWordsCount(std::ifstream& file) {
	file.clear();
	file.seekg(0, std::ios::beg);

	int cnt = 0;

	bool wordStarted = false;
	char c = ' ';
	while (file.peek() != EOF){
		c = file.get();

		if (IsWhiteSpace(c) && wordStarted){
			wordStarted = false;
			cnt++;
		}
		else if (!IsWhiteSpace(c) && !wordStarted) {
			wordStarted = true;
		}
	}
	if (wordStarted) cnt++;

	std::cout << "Words count --> " << cnt << std::endl;;
}

void PrintRowsCount(std::ifstream& file) {
	file.clear();
	file.seekg(0, std::ios::beg);

	int rows = 0; int charactersCnt = 0;
	while (!file.eof()){
		if (file.get() == '\n') rows++;
		charactersCnt++;
	}
	if(charactersCnt > 0) rows++;

	std::cout << "Rows count " << rows << std::endl;;
}

void PrintNonEmptyRowsCount(std::ifstream& file) {
	file.clear(); 
	file.seekg(0, std::ios::beg);

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
	double allCharacters = PrintFileLength(file);

	double nws = PrintNWSCCount(file);

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


