#include <iostream>
#include <fstream>
#include "Student.hpp"
#include "Helpers.hpp"

#define BUFFER 1024

#pragma warning(disable: 4996)

Student* readStudents(const char* fileName, int& size);
void readStudent(Student& student, std::ifstream& file);

Student* readStudents(const char* fileName, int& size) {
	char* buffer = new(std::nothrow) char[BUFFER];
	if (!buffer) return NULL;

	std::ifstream file(fileName);
	if (!file.is_open()){
		std::cerr << "Cannot open file!" << std::endl;
		return NULL;
	}

	int studentsCount = getLinesCount(file);
	Student* students = new(std::nothrow) Student[studentsCount];
	if (!students) {
		delete[] buffer;
		file.close();
		return NULL;
	}
	std::cout << file.tellg();

	int iter = 0;
	for (int i = 0; i < studentsCount; i++){
		Student student;
		readStudent(student, file);
		if (!student.name[0]) {
			delete[] buffer;
			delete[] students;
			file.close();
			return NULL;
		}

		students[iter++] = student;
	}

	delete[] buffer;
	file.close();
	size = studentsCount;
	return students;
}

void readStudent(Student& student, std::ifstream& file) {
	char FN[FN_SIZE] = {};
	file.getline(FN, FN_SIZE, ' ');

	char nameBuff[NAME_SIZE] = {};
	file.getline(nameBuff, NAME_SIZE);

	if (strlen(FN) != 10) return;

	strcpy(student.FN, FN);
	strcpy(student.name, nameBuff);
}

