
#include <assert.h>
#include "Person.hpp"
#pragma warning(disable: 4996)

constexpr char sexes[COUNT][7] = {"Male", "Female", "NA"};

// ctor/dtor
Person::Person(const char* f, const char* m, const char* l, const Date& date, const Sex& sex) :
	dateOfBirth(date), sex(sex), car(nullptr)
{
	if (!f) f = ""; if (!m) m = ""; if (!l) l = "";

	if (!set(fName, f) ||
		!set(mName, m) ||
		!set(lName, l)) {
		clearMemory();
		throw std::bad_alloc();
	}

	/* is this better
	fName = strcpy(new char[strlen(f) + 1], f);

	mName = new(std::nothrow) char[strlen(m) + 1];
	if (mName) strcpy(mName, m);
	else {
		clearMemory();
		throw std::bad_alloc();
	}

	lName = new(std::nothrow) char[strlen(l) + 1];
	if (lName) strcpy(lName, l);
	else {
		clearMemory();
		throw std::bad_alloc();
	}
	*/

}
Person::Person(const char* f, const char* m, const char* l, const Date& date, const Sex& sex, Car& car)
	: Person(f, m, l, date, sex)
{
	this->car = &car;
}
Person::Person(std::istream& is, int delim) :
	dateOfBirth(is),
	sex((Sex)readInt(is))
{
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if( !set(fName, readString(is, delim)) ||
		!set(mName, readString(is, delim)) || 
		!set(lName, readString(is, '\n'))) {
		clearMemory();
		throw std::invalid_argument("invalid params!");
	}

}
Person::Person(std::istream& is, Car& car, int delim)
	: Person(is, delim) 
{
	this->car = &car;
}
Person::~Person() noexcept 
{ 
	clearMemory();
	if (car) car->setOwner(nullptr);
}

// public 
bool Person::setFName(const char* what) {
	if (!what) return false;
	set(fName, what);
}
bool Person::setMName(const char* what) {
	if (!what) return false;
	set(mName, what);
}
bool Person::setLName(const char* what) {
	if (!what) return false;
	set(lName, what);
}

void Person::print() const {
	std::cout << "Name: " << fName << ' ' << mName << ' ' << lName << '\n';
	std::cout << "Sex: " << sexes[(int)sex] << '\n';
	std::cout << "Date of birth: ";
	dateOfBirth.print();
}
void Person::setCar(Car* car) {
	if (this->car == car) return;

	if (car) {
		if (this->car) this->car->setOwner(nullptr);
		car->setOwner(this);
	}
	this->car = car;
}
						
// private 
bool Person::set(char*& where, const char* what) {
	assert(what);

	char* temp = new(std::nothrow) char[strlen(what) + 1];
	if (!temp) return false;
	strcpy(temp, what);

	delete[] where;
	where = temp;

	assert(where != nullptr);
	return true;
}
const char* Person::readString(std::istream& is, char delim) {
	static char buffer[1024]{};
	if (!is) return buffer;

	is.getline(buffer, sizeof(buffer), delim);
	if (!is) return nullptr;
	return buffer;
}
const char* Person::copyString(const char* what) {
	if (!what) throw std::bad_alloc();

	char* t = new char[strlen(what) + 1];
	return strcpy(t, what);
}
int Person::readInt(std::istream& is) {
	int res;
	if (!(is >> res)) {
		throw std::invalid_argument("invalid params");
	}
	return res;
}
void Person::clearMemory(){
	delete[] fName;
	delete[] mName;
	delete[] lName;
	
}