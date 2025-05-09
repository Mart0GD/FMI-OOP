#define _CRT_SECURE_NO_WARNINGS

#include "Worker.h"
#include "Team.h"
#include "Helper.h"
#include <iostream>

/*
struct Team {
	char id[ID_LEN];
	char* name = {};
	Worker workers[MAX_WORKERS] = {};
	int workersCount;
};

*/
void read(Team& team) {
	std::cout << "Team ID -- > ";
	char* idBuff = readInputString(ID_LEN);
	if (!idBuff) return;
	strcpy(team.id, idBuff);

	std::cout << "Team name -- > ";
	char* nameBuff = readInputString(WORKER_MAX_NAME_LEN);
	if (!nameBuff) {
		free(team);
		return;
	}
	team.name = new(std::nothrow) char[strlen(nameBuff) + 1];
	strcpy(team.name, nameBuff);

	delete[] idBuff;
	delete[] nameBuff;
}

void print(const Team& team) {
	std::cout << "Name: " << team.name;
	std::cout << "\nWorkers count: " << team.workersCount << "\n";

	for (int i = 0; i < team.workersCount; i++){
		print(team.workers[i]);
	}
}

bool addWorker(Team& team, const Worker& worker) {
	if (team.workersCount >= MAX_WORKERS) return false;
	team.workers[team.workersCount++] = worker;
	return true;
}

int findWorkerIndex(const Team& team, const Worker& worker) {
	for (int i = 0; i < team.workersCount; i++){
		if (strcmp(team.workers[i].ID, worker.ID) == 0){
			return i;
		}
	}

	return -1;
}

void free(Team& team) {
	delete[] team.name;
	team.name = nullptr;
	for (int i = 0; i < team.workersCount; i++){
		free(team.workers[i]);
	}
}