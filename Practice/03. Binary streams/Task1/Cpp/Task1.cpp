#include <iostream>
#include <fstream>

#include "Person.hpp"
#pragma warning(disable: 4996)
/*


�������� ��������, ����� ������ � 2 �������� ������ � ���������� �� ���� �� ����������� �� ��������� ���:

Read �����
��� ��� ���� 1 �������� ��������, ����� � ��� ������������� ����� �� ������� ����. ���������� ������ �� ������� ���������� �� ����� �� ��� Person � �� �������� ���� ����� �� ���������.

Write �����
��� ��� ������ �� ����������� �� ��������� ��� �� ������ �� 1 � �� �������� (� �������� ���):

���, ����� ������������ ��� �� ����,
���, ����� ������������ ��� �� �����,
���, ����� ������������ ������� �� �����,
���� �����, ����� ������������ ������ �� �����,
������ �����, ����� ������������ ������ � ��������� �� �����.
�������� ��������� �� ���������� �� ���� �� ����������� � ������� ������. ��������� ������� � ��������� ��� Person � ����� ��������� ���� ��������� � ���������� ����.


*/

int main1(int argc, char* args[]) {

	char* fileName = new(std::nothrow) char[strlen(args[0])];
	if (!fileName) return -1;

	strcpy(fileName, args[1]);
	std::fstream file(fileName, std::ios::out | std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Cannot open file for read!";
		return -1;
	}

	Person p = {};
	if (argc - 1 == 1)
	{
		bool res = read(p, fileName);
		if (!res) return -1;
		printPerson(p);
	}
	else {
		createPerson(p, argc, args);
		write(p, fileName);
	}

	free(p);
}