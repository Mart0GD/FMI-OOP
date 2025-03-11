#include <cstdlib>
#include "Address.hpp"
#include "Student.hpp"
#include <iostream>
#include <cstring>

#pragma warning(disable : 4996)

int main() {
	srand(std::time(nullptr));

	Student student;
	Student student2;
	Student student3;
	Student student4;
	Student student5;
	Student student6;
	Student student7;

	RandomStudent(student);
	RandomStudent(student2);
	RandomStudent(student3);
	RandomStudent(student4);
	RandomStudent(student5);
	RandomStudent(student6);
	RandomStudent(student7);

	char** critiria = new(std::nothrow) char*[2];
	if (!critiria) return 1;

	for (int i = 0; i < 2; i++){
		critiria[i] = new(std::nothrow) char[MAX_NAME_LEN];
		if (!critiria[i]) return 1;
	}

	strcpy(critiria[0], student.name);
	strcpy(critiria[1], student3.surname);

	Student st[7] =
	{
		student,
		student2,
		student3,
		student4,
		student5,
		student6,
		student7
	};

	Student* best = getStudentWithGradesAbove(st, 5, 7);
	Student* bestOfKn = getStudentsWithMaximumGrades(st, 7, 2, Major::CS, 3);
	searchForStudents(st, critiria, 7, 2);

	freeStudent(student);
	freeStudent(student2);
	freeStudent(student3);
	freeStudent(student4);
	freeStudent(student5);
	freeStudent(student6);
	freeStudent(student7);
	return 0;
}