#pragma once
#include "Worker.h"

#define MAX_WORKERS 5
#define ID_LEN 10
#define MAX_NAME_LEN 128

/*
Дефинирайте структура за екип. Всеки екип има следните характеристики:

id -> идентификатор
име - низ с произволна дължина (няма да надвиши 128, но да бъде заделена само толкова колкото ни е нужна)
работници - масив с капацитет от 5 работника
брой на работниците в екипа - цяло число
*/

struct Team {
	char id[ID_LEN] = {};
	char* name = {};
	Worker workers[MAX_WORKERS] = {};
	unsigned workersCount = 0;
};


void read(Team& team);
void print(const Team& team);
bool addWorker(Team& team, const Worker& worker);
int findWorkerIndex(const Team& team, const Worker& worker);
void free(Team& team);