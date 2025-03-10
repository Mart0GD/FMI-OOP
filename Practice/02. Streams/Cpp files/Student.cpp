#include <cstring>
#include <iostream>
#include <fstream>
#include "Student.hpp"

#pragma warning(disable : 4996)

Student CreateStudent(char* info) {
	char fnameBuff[MAX_STUDENT_NAME] = {};

	char* ptr = strchr(info, ',');
	int index = ptr - info;
	strncpy(fnameBuff, info, index);
	info += index + 1;

	char lnameBuff[MAX_STUDENT_NAME] = {};

	ptr = strchr(info, ',');
	index = ptr - info;
	strncpy(lnameBuff, info, index);
	info += index + 1;

	char email[MAX_STUDENT_EMAIL] = {};

	ptr = strchr(info, ',');
	index = ptr - info;
	strncpy(email, info, index);
	info += index + 1;

	char FN[FN_SIZE] = {};

	strcpy(FN, info);
	info += index + 1;

	Student student = {};
	if (fnameBuff[0] && lnameBuff[0] && email[0] && FN[0]) {
		strcpy(student.fname, fnameBuff);
		strcpy(student.lname, lnameBuff);
		strcpy(student.email, email);
		strcpy(student.FN, FN);

		return student;
	}

	return {};
}

Student* GetStudent(const char FN[], Student* students, int studentsCount) {
	for (int i = 0; i < studentsCount; i++) {
		if (strcmp(FN, students[i].FN) == 0)
			return &students[i];
	}

	return NULL;
}

bool CreateCSVFile(const Student* students, const char* fileName, size_t studentsCount) {
	std::ofstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "File cannot be created!";
		return false;
	}

	for (int i = 0; i < studentsCount; i++){
		file
			<< students[i].fname << ","
			<< students[i].lname << ","
			<< students[i].email << ","
			<< students[i].FN;

		if (i + 1 < studentsCount) file << '\n';
	}

	file.close();
	return true;
}

void print(const Student& student) {
	std::cout << "\nStudent first name --> " << student.fname;
	std::cout << "\nStudent last name --> " << student.lname;
	std::cout << "\nStudent email --> " << student.email;
	std::cout << "\nStudent FN --> " << student.FN;
}
