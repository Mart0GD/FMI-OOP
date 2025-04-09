#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstring>

#include "Enums.hpp"
#include "Date.hpp"
#include "Car.hpp"
/*
Човекът трябва да има три имена (символни низове с произволна дължина), дата на раждане (обект Date) и пол (изброен тип). Нека датата на раждане и полът се задават при конструиране и не могат повече да се променят (данните са const). Имената трябва да могат да се променят свободно, но да не са празни. Подсигурете подходящи конструктори, деструктор и методи за достъп. Реализирайте метод за извеждане на данните на екрана.

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