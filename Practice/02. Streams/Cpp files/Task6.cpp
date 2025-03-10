#include<iostream>
#include<fstream>
#include "Student.hpp"

#define BUFFER 1028
#pragma warning(disable : 4996)

/*
Да се напише програма, която чете Comma-separated values (CSV) файл със студенти. За всеки студент има следната информация:

първо име,
фамилно име,
имейл,
факултетен номер.
Със стартирането на програмата потребителят въвежда име на файл, който да бъде зареден в паметта.

Да се напише функция, която след зареждане на файла отпечатва на стандартния изход информация за студента при подаден факултетен номер.
Да се напише функция, която по подаден факултетен номер и низ променя email-a на студента, който има дадения факултетен номер, с подадения низ.
Да се напише функция, която приема низ (име на файл) и запазва студентите в същия формат (CSV). Т.е. при повторно пускане, програмата да може да прочете новия генериран файл.
*/
int GetLines(std::ifstream& stream);

int main() {

	char* fileName = new(std::nothrow) char[BUFFER];
	std::cout << "Enter students file name --> ";
	std::cin >> fileName;

	std::ifstream file(fileName);
	if (!file.is_open()){
		std::cerr << "Cannot open file!" << std::endl;
		return 1;
	}

	char* info = new(std::nothrow) char[BUFFER];
	if (!info) return 1;

	int studentsCount = GetLines(file);
	file.close();
	file.open(fileName);


	Student curStudent = {};
	Student* students = new(std::nothrow) Student[studentsCount];
	if (!students) return -1;

	int index = 0;
	while (file.peek() != EOF) {
		file.getline(info, BUFFER);
		curStudent = CreateStudent(info);

		if (!curStudent.fname[0]) continue;
		students[index++] = curStudent;
	}

	char wantedFN[FN_SIZE] = {};

	std::cin.ignore();
	std::cout << "Enter faculty number of desired student --> ";
	std::cin.getline(wantedFN, FN_SIZE);
		
	Student* student = GetStudent(wantedFN, students, studentsCount);
	if (!student->fname[0]) {
		std::cerr << "No student with FN " << wantedFN << " could be found!" << std::endl;
	}
	else print(*student);

	std::cout << "\nEnter faculty number of desired student to change email --> ";
	std::cin.getline(wantedFN, FN_SIZE);

	char email[MAX_STUDENT_EMAIL] = {};
	std::cout << "Enter new email --> ";
	std::cin.getline(email, MAX_STUDENT_EMAIL);

	Student* studentToChange = GetStudent(wantedFN, students, studentsCount);
	strcpy(studentToChange->email, email);

	char* newFileName = new(std::nothrow) char[BUFFER];
	if (!newFileName) return 1;

	std::cout << "Enter new csv file name --> ";
	std::cin.getline(newFileName, BUFFER);

	bool res = CreateCSVFile(students, newFileName, studentsCount);
	if (!res) std::cout << "CSV file could not be created!";

	file.close();
	delete[] students;
	delete[] fileName;
	delete[] info;
	delete[] newFileName;

	students = nullptr;
	fileName = nullptr;
	newFileName = nullptr;
	info = nullptr;
	return 0;
}

int GetLines(std::ifstream& stream) {
	int lines = 0;
	while (!stream.eof()){
		if (stream.get() == '\n') lines++;
	}
	lines++;
	
	return lines;
}