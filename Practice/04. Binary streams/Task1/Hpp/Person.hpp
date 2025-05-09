#pragma once
#include <iostream>

/*
� ���������� �� ������� ��� ����������� Person:

��� -> ��� � ���������� �������
������� -> ��� � ���������� �������
������ -> ���� �����
����� � ��������� -> ������ �����
*/

struct Person {
	char* name{nullptr};
	char* lastName{nullptr};
	uint32_t age{};
	float_t weight{};
};

bool createPerson(Person& person, int argc, char* args[]);
void printPerson(Person& person);
bool read(Person& person, const char* fileName);
bool write(const Person& person, const char* fileName);

void free(Person& person);