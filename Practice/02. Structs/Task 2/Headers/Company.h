#pragma once
#include "Team.h"
#include "Worker.h"

#define MAX_TEAM_SIZE 5
#define MAX_COMPANY_NAME_LEN 128
/*
����������� ��������� �� ��������. ����� �������� ��� �������� ��������������:

��� - ��� � ���������� ������� (���� �� ������� 128, �� �� ���� �������� ���� ������� ������� �� � �����)
����� - ����� � ��������� �� 5 �����
���� �� ������� � ���������� - ���� �����
*/

struct Company {
	char* name = {};
	unsigned teamCount = 0;
	Team teams[MAX_TEAM_SIZE] = {};
};

Team* findWorkerTeam(Company& company, const Worker& worker);
int getTeamIndex(char* id, const Company& company);
void free(Company& company);