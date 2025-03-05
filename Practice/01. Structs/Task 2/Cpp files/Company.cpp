#include "Company.h"
#include <iostream>

Team* findWorkerTeam(Company& company, const Worker& worker) {
	for (int i = 0; i < company.teamCount; i++){
		for (int j = 0; j < company.teams[i].workersCount; j++){
			if (strcmp(company.teams[i].workers[j].ID, worker.ID) == 0){
				return &company.teams[i];
			}
		}
	}

	return nullptr;
}

int getTeamIndex(char* id, const Company& company) {
	for (int i = 0; i < company.teamCount; i++){
		if (strcmp(company.teams[i].id, id) == 0){
			return i;
		}
	}

	return -1;
}

void free(Company& company) {
	delete[] company.name;
	company.name = nullptr;
	for (int i = 0; i < company.teamCount; i++){
		free(company.teams[i]);
	}
}