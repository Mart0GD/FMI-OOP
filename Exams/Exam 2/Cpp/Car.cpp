#include "Car.hpp"
#pragma warning(disable: 4996)

Car::Car(const char* maker, const Date& dop, TrunkType trunkType, uint32_t hp, uint32_t seats) 
	: dop(dop), trunkType(trunkType), hp(hp), seats(seats)
{
	this->maker = copyString(maker);
	addToCombinedHP(hp);
}
Car::Car(std::istream& is) : trunkType(getTrunkType(readString(is, ' ')))
{
	if (!is || trunkType == Unknown) throw "ivalid file!";

	maker = copyString(readString(is, ' '));

	try
	{
		this->dop = Date(readString(is, ' '));
		is >> hp;
		if (!is) throw "bad file!";
		is >> seats;
		if (!is) throw "bad file!";
	}
	catch (const std::exception&)
	{
		delete[] maker;
	}
	is.ignore(1024, '\n');
	addToCombinedHP(hp);
}

Car::Car(const Car& other) 
	: maker(copyString(other.maker)), dop(other.dop), 
	  trunkType(other.trunkType), hp(other.hp), seats(other.seats)
{ 
	addToCombinedHP(hp);
}
Car& Car::operator=(const Car& other){
	if (this == &other) return *this;

	Car copy(other);
	*this = copy;

	return *this;
}

Car::Car(Car&& other) noexcept
	: trunkType(other.trunkType), dop(other.dop), 
	  hp(other.hp), seats(other.seats)
{
	maker = other.maker;
	other.maker = nullptr;
	addToCombinedHP(hp);
}
Car& Car::operator=(Car&& other) noexcept {
	if (this == &other) return *this;

	std::swap(maker, other.maker);
	std::swap(dop, other.dop);

	hp = other.hp;
	seats = other.seats;

	return *this;
}

Car::~Car() {
	delete[] maker;
	subtractFromCombinedHP(hp);
}

bool Car::serialize(const Car& car, std::ostream& os) {
	if (!os) return false;
	// Kombi Peugeot 12/11/2004 112 4 --> format

	os << trunkTypes[(int)car.trunkType] << ' ' << car.maker << ' '; 
	car.dop.print(os);
	os << ' '  << car.hp << ' ' << car.seats << '\n';
}

char* Car::readString(std::istream& is, int delim) {
	static char buff[1024]{};
	if (!is) return buff;

	is.getline(buff, sizeof(buff), delim);
	return buff;
}
char* Car::copyString(const char* what) {
	if (!what || !*what) throw std::invalid_argument("invalid string!");

	char* temp = new char[strlen(what) + 1];
	return strcpy(temp, what);
}
TrunkType Car::getTrunkType(const char* str) {
	for (int i = 0; i < COUNT; i++){
		if (!strcmp(str, trunkTypes[i])) return (TrunkType)i;
	}

	return Unknown;
}

uint32_t Car::combinedHP = 0;