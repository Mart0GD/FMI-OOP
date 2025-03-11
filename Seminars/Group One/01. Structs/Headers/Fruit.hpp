#pragma once
/*
������ 3. ����������� Fruit, ���������� ����, � ���������� �� ������� �����:
struct Fruit
{
  char name[32]; // ��� �� ����
  color cl;      // ���� �� ����
  yn annual;     // ����������� ����
  yn perennial;  // ������������ ����
  yn tropical;   // ���������� ����
};
������:
- color � ������� ��� �� ���� (����. brown, green, orange, red, yellow � �.�.)
- yn � ������� ��� � ��� ��������� Yes � No
�������� ��������, �����:
�) ������� ��������� ����� �� ��������� ��� ���������, �������� ������� � ������� ������� �� ������������;
�) ������� �� ���, ���� � ��������������� �� ����������� ���������, �������� ���� ������;
�) ������� ������� �� ���������, �������� ���� ������, ���� ����������� ��;
�) ������� ��������������, ���������� ������� � ����� ����, ��������� � �������� ��� �� ��� �� �����.
�� ����� �� �� ��������� ��������� �������. ���������� �� �� ����������� ���������� �� �������.
*/
#include "Enums.hpp"
#define NAME_LEN 32

struct Fruit {
	char name[NAME_LEN];
	Color color;
	YN annual;
	YN perennial;
	YN tropical;
};

Fruit CreateFruit();
int getWeight(const Fruit& fruit);
void SortFruits(Fruit* fruitsm, size_t count);
void PrintTropicalPerennialFruit(Fruit* fruits, size_t count, const Color color);
void PrintFruit(const Fruit& fruit);
const char* getColor(Color color);