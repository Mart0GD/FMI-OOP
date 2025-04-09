#ifndef CAR_REGISTER_HPP
#define CAR_REGISTER_HPP

#include "Car.hpp"
#include "Person.hpp"

/*
Реализирайте система (като клас), която поддържа множество коли и множество хора. Трябва да можете да генерирате различни справки, като:

колко хора са собственици на повече от една кола
колко коли нямат собственици
кои коли са собственост на даден човек
кои хора имат определен брой коли (0, 1, 2 и т.н.) Също да можете да прехвърлите кола към нов собственик (продажба). На този етап не се изисква добавяне или премахване на коли и хора в системата след създаването ѝ.
*/


class CarRegister {

public:
	CarRegister();

	bool createCar();

	std::size_t getCarsCount() const { return carsCnt; }
	std::size_t getCapacity() const { return capacity; }

	//std::size_t multipleCarOwnersCount() const;
	std::size_t getCarsWithNoOwnersCount() const;
	Car** getPersonCars(const Person& p) const;
	Person* getPersonWithCarCount(std::size_t count) const;
	bool sellCar(Person& person, Car& car);

	Car* extractCar(std::size_t index);
	bool insertCar(Car& car);

	~CarRegister() noexcept;

private:
	int getCarIndex(const Car& car);

private:
	Car** cars;

	std::size_t carsCnt{0};
	static const std::size_t capacity;
};

#endif