#include <iostream>
#include <fstream>
#include <iomanip>
#include "Student.hpp"
#include "Exam.hpp"

#define EXAMS_FILE_NAME "Exams.txt"
#define STUDENTS_FILE_NAME "Students.txt"
/*
������������ ������� ������� �� ����� ������� �� ����� �������� �� ������� ����������
� ��� ����� � "students.txt" � "exams.txt". ����� ��� �� ����� "students.txt" ���
������� ������ � "XXXX SSS�", ������ XXXX � ���������� ����� (���������������� ��
����� 10 �������), a SSS� � ����� �� ������� (��� � ������� �� 199 �������). �����
��� �� ����� "exams.txt" ��� ������� ������ � "XXXX YYYY SSS�", ������ XXXX �
���������� �����, YYYY � ������ �� ����� ������� (double), � SSS� � ����� ��
��������, �� ����� � ������� ����� (��� � ������� �� 199 �������).
������ �� ���� "students.txt"
0MI0101234 ���� ������
1MI0202345 ������ ��������
2MI0701234 ����� �������
3MI0100014 ����� ������

������ �� ���� "exams.txt"
0MI0101234 3.50 ������������� ������
3MI0100014 6.00 ��������� �� ����� � ������������
2MI0701234 4.50 ��������� �� ����� � ������������
3MI0100014 5.50 ������������� ������
0MI0101234 5.50 ��������� �� ����� � ������������
0MI0101234 4.50 ������������� ������
1MI0202345 3.30 ��������� �� ����� � ������������
0MI0101234 6.00 ������������� ������
��������� � ��� ����� "exams.txt" �� ��� ����� �� ��������, ����� �� �� ������� ���
����� "students.txt" � �������. �� �� ������ ��������, ����� �� ����� �� ����������
��� ����� "students.txt" ������ � ������� ������ ������������� �� ������ ������,
�������� �� ����� ������� �������.
������ �� ��������:
0MI0101234 ������������� ������ 4.7
0MI0101234 ��������� �� ����� � ������������ 5.5
2MI0701234 ��������� �� ����� � ������������ 4.5
1MI0202345 ��������� �� ����� � ������������ 3.3
3MI0100014 ��������� �� ����� � ������������ 6
3MI0100014 ������������� ������ 5.5

������ ������ ������, ��� �������, �� � ����� ����� �� ��������� � ��������� ��� ��
������������ ������.

*/

bool contains(char* FN, Student* students, size_t cnt) {
	for (int i = 0; i < cnt; i++){
		if (strcmp(students[i].FN, FN) == 0) return true;
	}

	return false;
}

int main7() {
	int studentsCount, examsCount;
	Student* students = readStudents(STUDENTS_FILE_NAME, studentsCount);
	Exam* exams = readExams(EXAMS_FILE_NAME, examsCount);

	std::ofstream file("Output.txt");
	if (!file.is_open()){
		std::cerr << "Cannot open fail!";
		return -1;
	}

	bool* checkedExamFlags = new(std::nothrow) bool[examsCount] {};
	if (!checkedExamFlags) return -1;

	for (int i = 0; i < examsCount; i++){
		if (!contains(exams[i].FN, students, studentsCount) || checkedExamFlags[i]) continue;

		file << exams[i].FN << ' ' << exams[i].subject << ' ';
		double grade = exams[i].grade;
		int gradesCount = 1;
		checkedExamFlags[i] = true;
		for (int j = i + 1; j < examsCount; j++){
			if (strcmp(exams[j].FN, exams[i].FN) == 0 && strcmp(exams[i].subject, exams[j].subject) == 0 && !checkedExamFlags[j]) {
				grade += exams[j].grade;
				gradesCount++;
				checkedExamFlags[j] = true;
			}
		}
		file << std::setprecision(2) << grade / gradesCount << '\n';
	}

	return 0;
}

