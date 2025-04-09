#ifndef CAR_HPP
#define CAR_HPP

#include "date.hpp"
#include "Person.hpp"
/*
������ ��� ����� � �����, ����� �� �������� ������ � ���������� �������, ���� �� ������������ (Date), ���� (unsigned int) � ���������� (Person). ������, ������� � ������ �� ������������ �� ����� �� �� �������� (��������� �� const), ������ ������ � ������� � ������ �� � � RGB ������ (���-������� ���� �� ������� � �������� �� �����, ������� - �� ������, ������� �� �������; ���-�������� ���� ������ �� � ������ 0), � ����������� � �������� ��� Person, ����� ���� �� � �������, �� ���� � �� �� � (nullptr), ������ ���� �����. �� ������ ������������ ��������� ������������ � ������ �� ������, ���� ��������� �� ������ � ����� �� ����������.
*/

class Person;

class Car {

public:
	Car(const char* model, const char* maker, const Date& dop, uint16_t color);
	Car(const char* model, const char* maker, const Date& dop, uint16_t color, Person& owner);
	Car(std::istream& is);
	Car(std::istream& is, Person& owner);
	Car(const Car& other);
	Car& operator=(Car&& car) = delete;

	void print() noexcept;

	const char* getModel() const { return model; }
	const char* getMaker() const { return maker; }
	const Date& getDop() const { return dop; }
	const Person* const getOwner() const { return owner; }
	void setOwner(Person* p);

	uint8_t getR() const;
	uint8_t getG() const;
	uint8_t getB() const;

	~Car() noexcept;

private:
	static char* copyString(const char* what);
	static const char* readString(std::istream& is, char delim);
	void clear();

private:
	const char* const model;
	const char* const maker;
	const Date dop;
	
	uint16_t color;
	Person* owner;

};

#endif