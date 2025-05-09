#include <iostream>

#include "Company.h"
#include "Team.h"
#include "Worker.h"
#include "Helper.h"

void findTeam(const Company& company);
bool createWorker(Worker& worker, Company& company);
Worker* findWorker(Company& company);
void findWorkersByName(const Company& company);
void findWorkerBoses(Company& company);
void deleteWorker(Company& company);
void deleteTeam(Company& company);
void readCmd(int& command);

int main() {
	std::cout << "Enter company name --> ";
	char* companyName = new(std::nothrow) char[MAX_COMPANY_NAME_LEN] {};
	if (!companyName) return 1;

	do{
		std::cin.getline(companyName, MAX_COMPANY_NAME_LEN);
	} while (!companyName[0]);

	Company company;
	company.name = companyName;

	int cmd = 0;
	Team team;
	Worker worker;
	while (true){
		readCmd(cmd);

		switch (cmd){

			case 1:
				if (company.teamCount >= MAX_TEAM_SIZE) continue;

				read(team);
				company.teams[company.teamCount++] = team;
				print(team);
			break;

			case 2:
				if (company.teamCount > 0);
				if (createWorker(worker, company)) print(worker);
			break;

			case 3:
				findTeam(company);
			break;

			case 4:
				worker = *findWorker(company);
				if(worker.name) print(worker);
			break;

			case 5:
				findWorkersByName(company);
			break;

			case 6:
				findWorkerBoses(company);
			break;

			case 7:
				deleteWorker(company);
			break;

			case 8:
				deleteTeam(company);
			break;

			default: break;
		}

	}

	free(company);
}

void findTeam(const Company& company) {
	char* id = readInputString(ID_LEN);
	if (!id) return;

	bool found = false;
	for (int i = 0; i < company.teamCount; i++) {
		if (strcmp(company.teams[i].id, id) == 0) {
			print(company.teams[i]);
			found = true;
			break;
		}
	}
	if (!found) std::cout << "No such team found!";
	delete[] id;
	id = nullptr;
}

bool createWorker(Worker& worker, Company& company) {
	bool res = read(worker);
	if (!res) return false;

	int teamNumber = 0;
	std::cout << "Choose team to put worker --> ";
	do
	{
		std::cin >> teamNumber;
	} while (teamNumber >= company.teamCount && teamNumber < 0 && teamNumber > MAX_TEAM_SIZE);

	bool boss = false;
	std::cout << "Does worker have boss?(1/0)";
	std::cin >> boss;
	if (boss) {
		std::cin.ignore();
		char* id = readInputString(ID_LEN);
		if (!id) {
			std::cerr << "Incorrect id!";
			free(worker);
			return false;
		}

		for (size_t i = 0; i < company.teamCount; i++) {
			for (int j = 0; j < company.teams[i].workersCount; j++) {
				if (strcmp(company.teams[i].workers[j].ID, id) == 0) {
					worker.boss = &company.teams[i].workers[j];
					break;
				}
			}
		}

		delete[] id;
		id = nullptr;
	}

	res = addWorker(company.teams[teamNumber], worker);
	if (!res) return false;
	return true;
}

Worker* findWorker(Company& company) {
	char* id = readInputString(ID_LEN);
	if (!id) return NULL;

	bool found = false;
	int teamIndex = 0, workerIndex = 0;
	for (int i = 0; i < company.teamCount; i++) {
		for (int j = 0; j < company.teams[i].workersCount; j++) {
			if (strcmp(company.teams[i].workers[j].ID, id) == 0) {
				teamIndex = i;
				workerIndex = j;
				found = true;
				break;
			}
		}
		if (found) break;
	}
	if (!found) std::cout << "No worker with such id can be found!" << std::endl;

	delete[] id;
	id = nullptr;
	return &company.teams[teamIndex].workers[workerIndex];
}

void findWorkersByName(const Company& company) {
	char* name = readInputString(WORKER_MAX_NAME_LEN);
	char* lastName = readInputString(WORKER_MAX_NAME_LEN);
	if (!name || !lastName) return;

	bool found = false;
	for (int i = 0; i < company.teamCount; i++) {
		for (int j = 0; j < company.teams[i].workersCount; j++) {
			if (strcmp(company.teams[i].workers[j].name, name) == 0 || strcmp(company.teams[i].workers[j].lastName, lastName) == 0) {
				print(company.teams[i].workers[j]);
				found = true;
			}
		}
	}
	if (!found) std::cout << "No workers with such names can be found!" << std::endl;

	delete[] name;
	name = nullptr;
	delete[] lastName;
	lastName = nullptr;
}

void findWorkerBoses(Company& company) {
	Worker worker = *findWorker(company);
	if (!worker.name) return;

	std::cout << "Worker: " << worker.name << ' ' << worker.lastName;
	int bossCnt = 0;
	while (worker.boss){
		worker = *worker.boss;
		std::cout << " Boss " << ++bossCnt << ". " << worker.name << ' ' << worker.lastName;
	}
}

void deleteWorker(Company& company) {
	Worker worker = *findWorker(company);
	if (!worker.name) return;

	for (int i = 0; i < company.teamCount; i++){
		for (int j = 0; j < company.teams[i].workersCount; j++){
			if (company.teams[i].workers[j].boss && strcmp(company.teams[i].workers[j].boss->ID, worker.ID) == 0){
				company.teams[i].workers[j].boss == worker.boss;
			}
		}
	}

	Team* team = findWorkerTeam(company, worker);
	int index = findWorkerIndex(*team, worker);
	free(team->workers[index]);
	for (int i = index; i < team->workersCount - 1; i++){
		team->workers[i] = team->workers[i + 1];
	}
	team->workersCount--;
}

void deleteTeam(Company& company) {
	char* id = readInputString(ID_LEN);
	if (!id) return;

	int teamIndex = getTeamIndex(id, company);
	free(company.teams[teamIndex]);
	for (int i = teamIndex; i < company.teamCount - 1; i++){
		company.teams[i] = company.teams[i + 1];
	}
	company.teamCount--;
}

void readCmd(int& command) {
	do
	{
		std::cin >> command;
	} while (command < 1 && command > 8);
}
