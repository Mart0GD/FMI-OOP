#include <iostream>
#include <fstream>
#include "Exam.hpp"
#include "Helpers.hpp"


#pragma warning(disable: 4996)

#define BUFFER 1024

Exam* readExams(const char* fileName, int& size) {
	char* buffer = new(std::nothrow) char[BUFFER];
	if (!buffer) return NULL;

	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Cannot open file!" << std::endl;
		return NULL;
	}

	int examsCount = getLinesCount(file);
	Exam* exams = new(std::nothrow) Exam[examsCount];
	if (!exams) {
		delete[] buffer;
		file.close();
		return NULL;
	}

	int iter = 0;
	for (int i = 0; i < examsCount; i++) {
		Exam exam;
		
		if (!readExam(exam, file)) {
			delete[] buffer;
			delete[] exams;
			file.close();
			return NULL;
		}

		exams[iter++] = exam;
	}

	delete[] buffer;
	size = examsCount;
	file.close();
	return exams;
}

bool readExam(Exam& exam, std::ifstream& file) {

	char FN[FN_SIZE] = {};
	file.getline(FN, FN_SIZE, ' ');
	if (!file) return false;

	double grade = 0;
	file >> grade;
	if (!file) return false;

	char ch = ' ';
	file >> ch;
	file.seekg(-1, std::ios::cur);
	if (!file) return false;

	char name[EXAM_STR_LEN] = {};
	file.getline(name, EXAM_STR_LEN);
	if (!file) return false;

	if (strlen(FN) != 10 || !name[0] || (grade < 2 || grade > 6)) return false;

	strcpy(exam.FN, FN);
	exam.grade = grade;
	strcpy(exam.subject, name);
}