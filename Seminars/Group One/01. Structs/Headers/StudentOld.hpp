#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#define MAX_NAME_LEN 32
#define MAX_EMAIL_LEN 32
#define FN_LEN 10

#include "Address.hpp"
#include "Enums.hpp"

struct Student {
	char name[MAX_NAME_LEN] = {};
	char surname[MAX_NAME_LEN] = {};
	char lastName[MAX_NAME_LEN] = {};
	Major major = MUnknown;
	char FN[FN_LEN] = {};
	char email[MAX_EMAIL_LEN] = {};
	unsigned course;
	unsigned stream;
	unsigned group;
	unsigned successfulExams;
	double* grades;
	Address address;

};

void readStudentInfo(Student& student);
void readStudentInfoFromFile(Student& student, char* fileName);
void printStudentInfo(Student& student);
void RandomStudent(Student& student);
double AverageGrade(Student& student);
const char* getMajor(Major major);

Student* getStudentWithGradesAbove(Student* students, double floor, size_t count);
Student* getStudentsWithMaximumGrades(Student* students, size_t sudentsCount, size_t desiredStudents, Major major, size_t successfulExams);
void searchForStudents(Student* students, char** critiria, size_t studentsCount, size_t criteriaCnt);

void freeStudent(Student& student);
#endif