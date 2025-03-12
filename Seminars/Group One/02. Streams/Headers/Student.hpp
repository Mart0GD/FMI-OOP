#pragma once
#ifndef  STUDENT_HPP
#define STUDENT_HPP

#define FN_SIZE 11
#define NAME_SIZE 200

struct Student {
	char FN[FN_SIZE] = {};
	char name[NAME_SIZE] = {};
};

Student* readStudents(const char* fileName, int& size);
void readStudent(Student& student, std::ifstream& file);

#endif
