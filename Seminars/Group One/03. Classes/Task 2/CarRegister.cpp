
#include <fstream>
#include "CarRegister.hpp"
#include "Helpers.hpp"
/*
Реализирайте система (като клас), която поддържа множество коли и множество хора. Трябва да можете да генерирате различни справки, като:

колко хора са собственици на повече от една кола
колко коли нямат собственици -
кои коли са собственост на даден човек -
кои хора имат определен брой коли (0, 1, 2 и т.н.) Също да можете да прехвърлите кола към нов собственик (продажба). На този етап не се изисква добавяне или премахване на коли и хора в системата след създаването ѝ. -
*/


constexpr std::size_t readBuffer{ 1024 };
const std::size_t CarRegister::capacity{ 50 };

// ctor/dtor
CarRegister::CarRegister() {
	cars = new Car*[capacity];

	for (int i = 0; i < capacity; i++){
		cars[i] = nullptr;
	}
};
CarRegister::~CarRegister() noexcept {
	for (int i = 0; i < carsCnt; i++){
		cars[i] = nullptr;
	}

	delete[] cars;
	cars = nullptr;
}

// public --> won't work no multiple cars functionality;
/*std::size_t CarRegister::multipleCarOwnersCount() const {

	Person** people = new(std::nothrow) Person * [carsCnt];
	if (!people) return -1;

	int uniquePeople = 0;
	int index;
	for (int i = 0; i < carsCnt; i++){
		if (!cars[i]->getOwner()) continue;

		index = -1;
		for (size_t i = 0; i < uniquePeople; i++){
			if (cars[i]->getOwner() == people[i]) index = i;
		}

		if (index == -1) { people[uniquePeople++] = (Person*)cars[i]->getOwner(); }
	}

	int* personCars = new(std::nothrow) int[uniquePeople] {};
	if (!personCars) {
		delete[] people;
		return -1;
	}

	for (int i = 0; i < uniquePeople; i++){
		for (int j = 0; j < carsCnt; j++){
			if (!cars[j]->getOwner()) continue;
			if ((Person*)cars[j]->getOwner() == people[i]) personCars[i]++;
		}
	}

	int count = 0;
	for (int i = 0; i < uniquePeople; i++){
		if (personCars[i] > 1) count++;
	}

	delete[] people;
	delete[] personCars;

	return count;
}*/ 
std::size_t CarRegister::getCarsWithNoOwnersCount() const  {
	std::size_t count = 0;
	for (int i = 0; i < carsCnt; i++) {
		if (cars[i]->getOwner() == nullptr) count++;
	}

	return count;
}

Car** CarRegister::getPersonCars(const Person& p) const {
	if (carsCnt <= 0) return nullptr;

	Car** p_cars = new Car * [carsCnt];
	int iter = 0;

	for (int i = 0; i < carsCnt; i++){
		if (cars[i]->getOwner() == &p) p_cars[iter++] = cars[i];
	}

	return p_cars;
}
Person* CarRegister::getPersonWithCarCount(std::size_t count) const {
	Person* desiredPerson = nullptr;

	Person** people = new Person*[carsCnt];
	if (!people) return nullptr;

	int* carCounts = new(std::nothrow) int[carsCnt];
	if (!carCounts) {
		delete[] people;
		return nullptr;
	}

	int uniquePeopleCount = 0;

	for (int i = 0; i < carsCnt; ++i) {
		Person* owner = (Person*)cars[i]->getOwner(); 

		int index = -1;
		for (int j = 0; j < uniquePeopleCount; ++j) {
			if (people[j] == owner) {
				index = j;
				break;
			}
		}

		if (index == -1) {
			people[uniquePeopleCount] = owner;
			carCounts[uniquePeopleCount] = 1;
			++uniquePeopleCount;
		}
		else {
			carCounts[index]++;
		}
	}

	for (int i = 0; i < uniquePeopleCount; ++i) {
		if (carCounts[i] == static_cast<int>(count)) {
			desiredPerson = people[i];
			break;
		}
	}

	delete[] people;
	delete[] carCounts;

	return desiredPerson;
}
bool CarRegister::sellCar(Person& person, Car& car) {
	if (!&person || !&car) return false;

	car.setOwner(&person);
	person.setCar(&car);
}

Car* CarRegister::extractCar(std::size_t index) {
	if (index >= capacity) return nullptr;

	Car* car = cars[index];
	cars[index] = nullptr;

	for (int i = index; i < carsCnt - 1; i++){
		cars[i] = cars[i] + 1;
	}
	cars[carsCnt--] = nullptr;

	return car;
}
bool CarRegister::insertCar(Car& car) { // Car*& car - защо бихме използвали референция към укзател тук 
	int pos = 0;
	while (pos < capacity && cars[pos] != nullptr) pos++;

	if (pos >= capacity || !&car) return false;
	cars[pos] = &car;
	carsCnt++;
	return true;
}

// private 
int CarRegister::getCarIndex(const Car& car) {
	for (int i = 0; i < capacity; i++) {
		if (&car == cars[i]) return i;
	}

	return -1;
}