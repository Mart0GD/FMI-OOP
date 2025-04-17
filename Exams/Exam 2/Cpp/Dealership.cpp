#include "Dealership.hpp"


Dealership::Dealership(int32_t capacity) 
	: capacity(capacity), profit(0), sells(0)
{
	cars = new Car * [capacity] {};
	for (int i = 0; i < capacity; i++) {
		cars[i] = nullptr;
	}

	prices = new(std::nothrow) double[capacity];
	if (!prices) {
		delete[] cars;
		throw std::bad_alloc();
	}
	for (int i = 0; i < capacity; i++) prices[i] = -1;
}

Dealership::Dealership(const Dealership& other)
	:capacity(other.capacity)
{
	cars = new Car * [capacity];

	prices = new(std::nothrow) double[capacity];
	if (!prices) {
		delete[] cars;
		throw std::bad_alloc();
	}

	for (int i = 0; i < capacity; i++) {
		try
		{
			Car* car = new Car(*other.cars[i]);
			add(car, other.prices[i]);
		}
		catch (const std::exception&)
		{
			for (int ii = 0; ii < i; ii++)
			{
				delete cars[i];
			}
			delete[] cars;
			delete[] prices;
		}
		
	}

	profit = other.profit;
	sells = other.sells;
}
Dealership& Dealership::operator=(const Dealership& other) {
	if (this == &other) return *this;

	Dealership copy(other);
	*this = other;

	return *this;
}

Dealership::Dealership(Dealership&& other) noexcept
	: capacity(other.capacity)
{
	cars = other.cars;
	prices = other.prices;

	other.cars = nullptr;
	other.prices = nullptr;

	profit = other.profit;
	sells = other.sells;
}
Dealership& Dealership::operator=(Dealership && other) noexcept {
	if (this == &other) return *this;

	std::swap(cars, other.cars);
	std::swap(prices, other.prices);

	profit = other.profit;
	sells = other.sells;

	return *this;
}

Dealership::~Dealership() noexcept {
	for (int i = 0; i < capacity; i++)
	{
		delete cars[i];
	}
	delete[] cars;
	delete[] prices;
}

bool Dealership::add(Car*& car, double price) {
	int index = 0;
	while (index < capacity && cars[index] != nullptr) index++;

	if (!car || index == capacity) return false;
	cars[index] = car;
	prices[index] = price;
	car = nullptr;

	return true;
}
Car* Dealership::sell(int32_t index) {
	if (index > capacity) return nullptr;

	Car* car = cars[index];
	cars[index] = nullptr;
	profit += prices[index];
	sells++;

	prices[index] = -1;

	return car;
}

void Dealership::stats() {
	std::cout << "Profit --> " << profit << " " << "Sells --> " << sells << std::endl;
}

void Dealership::printFiltered(const char* maker) {
	for (int i = 0; i < capacity; i++)
	{
		if (cars[i] && strcmp(maker, cars[i]->getMaker()) == 0) {
			Car::serialize(*cars[i], std::cout);
			std::cout << std::endl;
		}
	}
}
void Dealership::printFiltered(double priceCap) {
	for (int i = 0; i < capacity; i++)
	{
		if (cars[i] && prices[i] <= priceCap) {
			Car::serialize(*cars[i], std::cout);
			std::cout << std::endl;
		}
	}
}
void Dealership::printFiltered(const Date& dop){

	for (int i = 0; i < capacity; i++){
		if (cars[i] && cars[i]->getDateOfProduction().equals(dop) > 0) {
			Car::serialize(*cars[i], std::cout);
			std::cout << std::endl;
		}
	}
}