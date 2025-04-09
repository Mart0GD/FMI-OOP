#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstring>

#include "Enums.hpp"
#include "Date.hpp"
#include "Car.hpp"
/*
������� ������ �� ��� ��� ����� (�������� ������ � ���������� �������), ���� �� ������� (����� Date) � ��� (������� ���). ���� ������ �� ������� � ����� �� ������� ��� ������������ � �� ����� ������ �� �� �������� (������� �� const). ������� ������ �� ����� �� �� �������� ��������, �� �� �� �� ������. ����������� ��������� ������������, ���������� � ������ �� ������. ������������ ����� �� ��������� �� ������� �� ������.

*/

class Car;

class Person {

public:
	Person() = delete;
	Person(const char* f, const char* m, const char* l, const Date& date, const Sex& sex);
	Person(const char* f, const char* m, const char* l, const Date& date, const Sex& sex, Car& car);
	Person(std::istream& is, int delim = ' ');
	Person(std::istream& is, Car& car, int delim = ' ');

	bool setFName(const char* what);
	bool setMName(const char* what);
	bool setLName(const char* what);

	void print() const;
	void setCar(Car* car);
	~Person() noexcept;

private:
	static const char* readString(std::istream& is, char delim);
	static const char* copyString(const char* what);
	static int readInt(std::istream& is);
	static bool set(char*& where, const char* what);
	void clearMemory();
	
private:
	char* fName; char* mName; char* lName;
	const Date dateOfBirth;
	const Sex sex;

	Car* car;
};

#endif