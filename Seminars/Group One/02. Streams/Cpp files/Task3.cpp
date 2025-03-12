#include <iostream>
#include <fstream>

#define MAX_FILE_NAME 64
/*
�������� ��������, ����� ������� �� ����������� ���� ��� �� ������� ����. ��� ������
�� � �������� �� ���� �����, ��������� � ���� ��� ������ ������ �������. ����� � ��
�� �������� ��� �������: 1) ���� ������ � � �������� ������ � 2) ���� ������� � ����
�� ��������� � ��������� ���.
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
