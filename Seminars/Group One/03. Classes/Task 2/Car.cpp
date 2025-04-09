
#include <assert.h>
#include <fstream>
#include "Car.hpp"

#pragma warning(disable: 4996)

constexpr std::size_t byte_size{ 4 };

// ctor/dtor
Car::Car(const char* model, const char* maker, const Date& dop, uint16_t color = 1) :
	model(copyString(model)), maker(copyString(model)), dop(dop)
{
	color = color << byte_size; color = color >> byte_size;
	owner = nullptr;
}
Car::Car(const char* model, const char* maker, const Date& dop, uint16_t color, Person& owner) 
	: Car(model, maker, dop, color = 1)
{
	this->owner = &owner;
}
Car::Car(std::istream& is) :
	model(copyString(readString(is, ','))),
	maker(copyString(readString(is, ','))),
	dop(is, '-'){

	is.ignore(std::numeric_limits<std::streamsize>::max(), ',');
	if (!(is >> color)){
		clear();
		throw std::invalid_argument("worong params!");
	}
	color = color << byte_size; color = color >> byte_size;
	owner = nullptr;
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
Car::Car(std::istream& is, Person& owner) : Car(is) 
{
	this->setOwner(&owner);
}
Car::Car(const Car& other):
	model(copyString(other.model)), 
	maker(copyString(other.maker)),
	dop(other.dop)
{
	owner = other.owner; // a person can have multiple cars!
	color = other.color;
}
Car::~Car() noexcept 
{
	clear(); 
	if (owner) owner->setCar(nullptr);
}

//public 


uint8_t Car::getB() const { return (color << (3 * byte_size)) >> ((3 * byte_size)); }
uint8_t Car::getG() const { return (color << (2 * byte_size)) >> ((3 * byte_size)); }
uint8_t Car::getR() const { return (color << (1 * byte_size)) >> ((3 * byte_size)); }

void Car::setOwner(Person* p) {
	if (this->owner == p) return;

	if (this->owner) this->owner->setCar(nullptr);
	this->owner = p;
	if (this->owner) this->owner->setCar(this);
}
void Car::print() noexcept {
	std::cout
	<< "Model: " << model << ' ' 
	<< "Maker: " << maker << ' ' 
	<< "Color: " << "(" << getR() << ',' << getG() << ',' << getB() << ')' << ' '
	<< "Date of production: ";
	dop.print();
}

// private 
char* Car::copyString(const char* what) {
	if (!what) throw std::bad_alloc();

	char* t = new char[strlen(what) + 1]; // leaving it open for exceptions
	return strcpy(t, what);
}
void Car::clear() {
	delete[] (char*)model;
	delete[] (char*)maker;
}
const char* Car::readString(std::istream& is, char delim = '\n') {
	static char buff[1024];
	if (!is) return buff;

	is.getline(buff, sizeof(buff), delim);
	if (!is) return nullptr;
	return buff;
}