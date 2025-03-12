#include <iostream>
#include <cstdlib>
#include "../Headers/Helpers.hpp"
#include "../Headers/Student.hpp"

#pragma warning(disable : 4996)

/*
Да се реализира структура, която представлява студент. Той се състои от:
Име, презиме, фамилия - всеки от тях символен низ с не повече от 32 символа; Адрес - от горния тип; Специалност - едно от предварително зададени опции (изброен тип); Факултетен номер - символен низ с 10 символа; e-mail - символен низ с не по-вече от 32 символа; курс, поток, група, брой успешно положени изпити, оценки от тези изпити - за тях подберете подходящи типове.
За студентите реализирайте функционалности за:
- прочитане на данни за студент то стандартния вход
- извеждане на данни за студент на стандартния вход
- генериране на случайни, но валидни данни за студент
- пресмятане на средния успех от положените изпити
Напишете функции, работещи с масив от записи за студенти, които:
- намира и връща като резултат всички студенти, които имат успех по-голям от даден праг (например отличници).
- намира определен брой студенти за дадена специалност с максимален успех, които имат поне даден брой успешно положени изпит.
- Извежда информация за студентите, намерени сред всички по едно или няколко от полетата: име, презиме, фамилия, факултетен номер. Позволете подаването на критерия да бъде като масив от низове и подходящи други параметри, определящи какви полета точно ще бъдат използвани при търсенето.
*/

void readStudentInfo(Student& student) {
	std::cout << "Name: ";
	std::cin.getline(student.name, sizeof(student.name) / sizeof(student.name[0]));

	std::cout << "Surname: ";
	std::cin.getline(student.surname, sizeof(student.surname) / sizeof(student.surname[0]));

	std::cout << "Last name: ";
	std::cin.getline(student.lastName, sizeof(student.lastName) / sizeof(student.lastName[0]));

	std::cout << "Address: ";
	ReadAddress(student.address);
	std::cin.ignore();

	int major = 0;
	std::cout << "Major: ";
	std::cin >> major;
	student.major = (Major)major;
	std::cin.ignore();

	std::cout << "FN: ";
	std::cin.getline(student.FN, sizeof(student.FN) / sizeof(student.FN[0]));

	std::cout << "Email: ";
	std::cin.getline(student.email, sizeof(student.email) / sizeof(student.email[0]));

	std::cout << "Course: ";
	std::cin >> student.course;

	std::cout << "Stream: ";
	std::cin >> student.stream;

	std::cout << "Group: ";
	std::cin >> student.group;

	std::cout << "SuccessfulExams: ";
	std::cin >> student.successfulExams;

	student.grades = new(std::nothrow) double[student.successfulExams];
	if (!student.grades) return;
	std::cout << "Grades: \n";
	for (int i = 0; i < student.successfulExams; i++){
		std::cout << i + 1 << ". ";
		std::cin >> student.grades[i];
	}
}	  

void printStudentInfo(Student& student) {
	std::cout << "Name: " << student.name;
	std::cout << "\nSurname: " << student.surname;
	std::cout << "\nLast name: " << student.lastName;

	std::cout << "\nAddress: ";PrintAddress(student.address);
	std::cout << "Major: " << getMajor(student.major);
	std::cout << "\nFN: " << student.FN;
	std::cout << "\nEmail: " << student.email;
	std::cout << "\nCourse: " << student.course;
	std::cout << "\nStream: " << student.stream;
	std::cout << "\nGroup: " << student.group;
	std::cout << "\nSuccessful exams: " << student.successfulExams;
	std::cout << "\nGrades: ";

	for (int i = 0; i < student.successfulExams; i++){
		std::cout << '\n' << i + 1 << ". " << student.grades[i];
	}
}

void RandomStudent(Student& student) {
	strcpy(student.name, generateRandomText(rand() % MAX_NAME_LEN));
	strcpy(student.surname, generateRandomText(rand() % MAX_NAME_LEN));
	strcpy(student.lastName, generateRandomText(rand() % MAX_NAME_LEN));

	Address address;
	RandomAddress(address);
	student.address = address;

	student.major = (Major)(rand() % MCOUNT);
	strcpy(student.FN, ToString(1000000000LL + rand() % 9000000000LL));

	strcpy(student.email, generateRandomText(rand() % MAX_EMAIL_LEN));

	student.course = (rand() % 3) + 1;

	student.stream = (rand() % 1) + 1;

	student.group = (rand() % 5) + 1;

	student.successfulExams = (rand() % 3) + 1;

	student.grades = new(std::nothrow) double[student.successfulExams];
	if (!student.grades) return;
	std::cout << "Grades: \n";
	for (int i = 0; i < student.successfulExams; i++) {
		float rnd = (float)(rand()) / RAND_MAX * 3.00;
		rnd += 3.00;
		student.grades[i] = rnd;
	}
}

double AverageGrade(Student& student) {
	double grade = 0;
	for (int i = 0; i < student.successfulExams;i++) {
		grade += student.grades[i];
	}
	return grade / student.successfulExams;
}

Student* getStudentWithGradesAbove(Student* students, double floor, size_t count) {
	Student* chosen = new(std::nothrow) Student[count];
	if (!chosen) return NULL;

	int iter = 0;
	for (int i = 0; i < count; i++){
		if (AverageGrade(students[i]) >= floor){
			chosen[iter++] = students[i];
		}
	}

	Student* chosenNew = new(std::nothrow) Student[iter];
	if (!chosenNew) return NULL;

	for (int i = 0; i < iter; i++){
		chosenNew[i] = chosen[i];
	}
	delete[] chosen;
	chosen = nullptr;

	return chosenNew;
}

Student* getStudentsWithMaximumGrades(Student* students, size_t sudentsCount, size_t desiredStudents, Major major, size_t successfulExams) {
	Student* chosenFromMajor = new(std::nothrow) Student[sudentsCount];
	if (!chosenFromMajor) return NULL;

	int iter = 0;
	for (int i = 0; i < sudentsCount; i++){
		if (students[i].major == major && students[i].successfulExams >= successfulExams)
			chosenFromMajor[iter++] = students[i];
	}

	int swapped = 0;
	Student temp = {};
	for (int i = 0; i < iter; i++){
		swapped = 0;
		for (int j = 0; j < iter - 1 - i; j++){
			if (AverageGrade(chosenFromMajor[j]) >= AverageGrade(chosenFromMajor[j + 1])) continue;

			temp = chosenFromMajor[j];
			chosenFromMajor[j] = chosenFromMajor[j + 1];
			chosenFromMajor[j + 1] = temp;
			swapped = 1;
		}
		if (!swapped) break;
	}

	int count = iter >= desiredStudents ? desiredStudents : iter;
	Student* finalRes = new(std::nothrow) Student[count];
	if (!finalRes) return NULL;

	for (int i = 0; i < count; i++){
		finalRes[i] = chosenFromMajor[i];
	}

	delete[] chosenFromMajor;
	chosenFromMajor = nullptr;
	return finalRes;
}

const char* getMajor(Major major) {
	const char* majors[CCOUNT] = {
	"INF",
	"IS",
	"CS",
	"SI"
	};

	return majors[(int)major];
}

void searchForStudents(Student* students, char** critiria, size_t studentsCount, rsize_t criteriaCnt) {
	Student* chosenStudents = new(std::nothrow) Student[studentsCount];
	if (!chosenStudents) return;

	int iter = 0;
	for (int i = 0; i < criteriaCnt; i++){
		for (int j = 0; j < studentsCount; j++){
			if (strcmp(critiria[i], students[j].name) == 0 || 
				strcmp(critiria[i], students[j].surname) == 0 ||
				strcmp(critiria[i], students[j].lastName) == 0 ||
				strcmp(critiria[i], students[j].FN) == 0)
			{
				chosenStudents[iter++] = students[j];
			}
		}
	}

	for (int i = 0; i < iter; i++){
		printStudentInfo(chosenStudents[i]);
	}

	delete[] chosenStudents;
	chosenStudents = nullptr;
}

void freeStudent(Student& student) {
	delete[] student.grades;
	student.grades = nullptr;
}