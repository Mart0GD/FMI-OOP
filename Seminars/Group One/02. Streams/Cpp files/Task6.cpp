#include <iostream>
#include <fstream>

#define FILE_NAME "Compress.txt"
#define OUTPUT_NAME "Output.txt"
#define MAX_FILE_NAME 128
/*
������ 6.
�������� ��������, ����� �������� ������� ����, ���� ������ ����� ������� �� ��� ���
������ �������������� ������ ������� � ������ ������ ������.
*/

int main6() {
	std::ifstream in(FILE_NAME);
	std::ofstream out(OUTPUT_NAME);
	if (!in || !out) {
		std::cerr << "Cannot open file!" << std::endl;
	}

	int cnt = 0;
	char current = ' ';
	char prev = -1;
	while (in){
		in.get(current);
		if (std::isspace(current)) {
			if (!std::isspace(prev)) {
				out << current;
			}
		}
		else out << current;
		prev = current;
	}

	in.close();
	out.close();
	return 0;
} 