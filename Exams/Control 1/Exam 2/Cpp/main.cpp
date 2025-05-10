#include "Car.hpp"
#include "Dealership.hpp"
#include "Date.hpp"

#include <fstream>

int main() {

	try
	{
		Date d1(12, 11, 2005);
		Date d2("01/12/1999");
		Date d3(1, 07, 2013);

		std::ifstream file("Cars.txt");
		if (!file.is_open()) throw "bad file!";

		std::ofstream file2("CarsOut.txt", std::ios::out);
		if (!file2.is_open()) throw "bad file!";

		Car* car1 = new Car(file);

		Car::serialize(*car1, file2);

		Car* car2 = new Car("Renault", d2, Hatchback, 140, 4);
		Car* car3 = new Car("BMW", d3, Sedan, 300, 4);
		Car* car4 = new Car("BMW", d3, Kombi, 190, 5);
		Car* car5 = new Car("BMW", d2, Kombi, 190, 5);

		Dealership d(4);

		d.add(car1, 3000);
		d.add(car2, 1000);
		d.add(car3, 12000);
		d.add(car4, 8000);
		d.add(car5, 10000);

		d.sell(2);

		d.stats();

		d.printFiltered("BMW");
		d.printFiltered(d2);
		d.printFiltered(4000);

	}
	catch (const std::exception&)
	{

	}
	

	return 0;
}