#pragma once
#include "Team.h"
#include "Worker.h"

#define MAX_TEAM_SIZE 5
#define MAX_COMPANY_NAME_LEN 128
/*
Дефинирайте стурктура за компания. Всяка компания има следните характеристики:

име - низ с произволна дължина (няма да надвиши 128, но да бъде заделена само толкова колкото ни е нужна)
екипи - масив с капацитет от 5 екипа
брой на екипите в компанията - цяло число
*/

struct Company {
	char* name = {};
	unsigned teamCount = 0;
	Team teams[MAX_TEAM_SIZE] = {};
};

Team* findWorkerTeam(Company& company, const Worker& worker);
int getTeamIndex(char* id, const Company& company);
void free(Company& company);