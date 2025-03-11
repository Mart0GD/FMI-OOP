#pragma once
#ifndef ADDRESS_H
#define ADDRESS_H
#define MAX_TOWN_LEN 32
#define MAX_STREET_LEN 64
/*
������ 4.
�� �� ��������� ���������, ����� ��������� �����. ��� �� ������ �� ���� (�������� ��� � �� ������ �� 32 �������); �������� ��� (���� ����� ��� ����); ����� (�������� ��� � �� ������ �� 64 �������); ����� (���� ����� ��� ����); ���� ����� (��� ������); ����, ����, ���������� (����� ���� ����� ��� ����). �������� ����� �� ���: "�����", 1234, "��. ��� ������", 10 �, ��. 2, ��. 7, ��. 30.
�� �� ������� ������, ����������� ��������� � ��������� �� ����� �� ����������� ���� / �����.

*/

struct Address {
	char town[MAX_TOWN_LEN] = {};
	unsigned postalCode;
	char street[MAX_STREET_LEN] = {};
	unsigned streetNumber;
	char streetLetter;
	unsigned short entrance;
	unsigned short floor;
	unsigned short apt;
}; 

void ReadAddress(Address& address);
void RandomAddress(Address& address);
void PrintAddress(const Address& address);

#endif