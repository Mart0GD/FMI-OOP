#include <iostream>
#include <fstream>
#include <iomanip>
#include "Student.hpp"
#include "Exam.hpp"

#define EXAMS_FILE_NAME "Exams.txt"
#define STUDENTS_FILE_NAME "Students.txt"
/*
Преподавател записва данните от текущ контрол на група студенти по няколко дисциплини
в два файла – "students.txt" и "exams.txt". Всеки ред от файла "students.txt" има
следния формат – "XXXX SSS…", където XXXX е факултетен номер (последователност от
точно 10 символа), a SSS… е името на студент (низ с дължина до 199 символа). Всеки
ред от файла "exams.txt" има следния формат – "XXXX YYYY SSS…", където XXXX е
факултетен номер, YYYY е оценка от текущ контрол (double), а SSS… е името на
предмета, по който е положен изпит (низ с дължина до 199 символа).
Пример за файл "students.txt"
0MI0101234 Иван Петров
1MI0202345 Стефан Стефанов
2MI0701234 Мария Иванова
3MI0100014 Петър Петров

Пример за файл "exams.txt"
0MI0101234 3.50 Математически анализ
3MI0100014 6.00 Структури от данни и програмиране
2MI0701234 4.50 Структури от данни и програмиране
3MI0100014 5.50 Математически анализ
0MI0101234 5.50 Структури от данни и програмиране
0MI0101234 4.50 Математически анализ
1MI0202345 3.30 Структури от данни и програмиране
0MI0101234 6.00 Математически анализ
Допустимо е във файла "exams.txt" да има данни за студенти, които не са описани във
файла "students.txt" и обратно. Да се напише програма, която за всеки от студентите
във файла "students.txt" намира и извежда средно аритметичното от всички оценки,
получени по всеки отделен предмет.
Пример за резултат:
0MI0101234 Математически анализ 4.7
0MI0101234 Структури от данни и програмиране 5.5
2MI0701234 Структури от данни и програмиране 4.5
1MI0202345 Структури от данни и програмиране 3.3
3MI0100014 Структури от данни и програмиране 6
3MI0100014 Математически анализ 5.5

Решете същата задача, при условие, че и двата файла са подредени в нарастващ ред на
факултетните номера.

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

