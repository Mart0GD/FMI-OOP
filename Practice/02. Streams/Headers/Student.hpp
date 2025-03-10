#pragma once
#ifndef STUDENT_HPP
#define STUDENT_HPP

#define MAX_STUDENT_NAME 64
#define MAX_STUDENT_EMAIL 128
#define FN_SIZE 11

struct Student {
	char fname[MAX_STUDENT_NAME] = {};
	char lname[MAX_STUDENT_NAME] = {};
	char email[MAX_STUDENT_EMAIL] = {};
	char FN[FN_SIZE] = {};
};

Student CreateStudent(char* info);
Student* GetStudent(const char FN[], Student* students, int studentsCount);
bool CreateCSVFile(const Student* students, const char* fileName, size_t studentsCount);
void print(const Student& student);
#endif