#include <iostream>
#include "Worker.h"
#include "Helper.h"

#pragma warning(disable : 4996)

bool read(Worker& worker) {
	std::cout << "Worker ID --> ";\
	char* idBuffer = readInputString(ID_LEN);
	if (!idBuffer) return false;
	strcpy(worker.ID, idBuffer);

	std::cout << "Worker name --> ";
	char* name = readInputString(WORKER_MAX_NAME_LEN);
	if (!name) {
		free(worker);
		return false;
	}
	worker.name = new(std::nothrow) char[strlen(name) + 1];
	strcpy(worker.name, name);

	std::cout << "Worker last name --> ";
	char* lastName = readInputString(WORKER_MAX_NAME_LEN);
	if (!lastName) {
		free(worker);
		return false;
	}
	worker.lastName = new(std::nothrow) char[strlen(lastName) + 1];
	strcpy(worker.lastName, lastName);

	std::cout << "Worker salary --> ";
	double salary = 0;
	do
	{
		std::cin >> salary;
	} while (salary <= 0);
	worker.salary = salary;

	return true;
}

void print(const Worker& worker) {
	std::cout << "Name: " << worker.name;
	std::cout << "\nLast name: " << worker.lastName;
	std::cout << "\nSalary: " << worker.salary;
	if (worker.boss) std::cout << "\nBoss: " << worker.boss->name << ' ' << worker.boss->lastName << std::endl;
	else std:: cout << std::endl;
}

void free(Worker& worker){
	delete[] worker.name;
	delete[] worker.lastName;

	worker.name = nullptr;
	worker.lastName = nullptr;
	worker.boss = nullptr;
}
