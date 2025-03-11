#include <iostream>
#include <cstring>
#include "Fruit.hpp"

#pragma warning(disable : 4996)

Fruit CreateFruit() {
	Fruit fruit;
	char buff[NAME_LEN] = {};

	std::cin.ignore();
	std::cin.getline(buff, NAME_LEN);

	if (!buff[0]) strcpy(buff, "Orange");
	strcpy(fruit.name, buff);

	int value = 0;
	std::cout << "Color --> ";
	std::cin >> value;
	fruit.color = (Color)value;

	bool isAnnual;
	bool isPerennial;
	bool isTropical;

	std::cout << "Annual --> ";
	std::cin >> isAnnual;

	std::cout << "Perennial --> ";
	std::cin >> isPerennial;

	std::cout << "Tropical --> ";
	std::cin >> isTropical;

	fruit.annual = (YN)isAnnual;
	fruit.perennial = (YN)isPerennial;
	fruit.tropical = (YN)isTropical;

	return fruit;

}

int getWeight(const Fruit& fruit) {
	return fruit.annual + (fruit.perennial * 2);
}

const char* getColor(Color color) {
	const char* colors[CCOUNT] = {
	"Brown",
	"Green",
	"Orange",
	"Red",
	"Yellow"
	};

	return colors[(int)color];
}

// сортира по име, цвят и продължителност на плододаване плодовете, зададени чрез масива;
void SortFruits(Fruit* fruits, size_t count) {
	int nameComparisson = 0;
	int colorComparison = 0;
	int weightComparison = 0;

	
	int swapped = 0;
	bool swap = 0;
	Fruit temp = {};
	for (int i = 0; i < count - 1; i++){
		swapped = 0;
		for (size_t j = 0; j < count - i - 1; j++){
			swap = 0;

			nameComparisson = strcmp(fruits[j].name, fruits[j + 1].name);
			if (nameComparisson > 0) swap = true;
			else if (nameComparisson == 0) {
				colorComparison = strcmp(getColor(fruits[j].color), getColor(fruits[j + 1].color));
				if (colorComparison > 0) swap = true;
				else if (colorComparison == 0 && getWeight(fruits[j]) < getWeight(fruits[j + 1])) swap = true;
			}
			
			if (!swap) continue;
			temp = fruits[j];
			fruits[j] = fruits[j + 1];
			fruits[j + 1] = temp;
			swapped = 1;
		}
		if (!swapped) break;
	}
}

// извежда многогодишните, тропически плодове с даден цвят, сортирани в низходящ ред по име на плода.
void PrintTropicalPerennialFruit(Fruit* fruits, size_t count, const Color color) {
	Fruit* selected = new(std::nothrow) Fruit[count];
	if (!selected) return;
	int selectedCnt = 0;

	for (int i = 0; i < count; i++)
		if (fruits[i].color == color && fruits[i].perennial && fruits[i].tropical) selected[selectedCnt++] = fruits[i];

	int swapped = 0;
	Fruit temp = {};
	for (size_t i = 0; i < selectedCnt; i++){
		for (int j = 0; j < selectedCnt - 1 - i; j++){
			if (strcmp(fruits[j].name, fruits[j + 1].name) <= 0) continue;

			fruits[j] = temp;
			fruits[j] = fruits[j + 1];
			fruits[j + 1] = temp;
			swapped = 1;
		}
		if (!swapped) break;
	}

	for (int i = 0; i < selectedCnt; i++){
		PrintFruit(fruits[i]);
	}

	delete[] selected;
	selected = nullptr;
}

void PrintFruit(const Fruit& fruit) {
	std::boolalpha;
	std::cout << "Name: " << fruit.name << std::endl;
	std::cout << "Color: " << fruit.color << std::endl;
	std::cout << "Annual: " << fruit.annual << std::endl;
	std::cout << "Perennial: " << fruit.perennial << std::endl;
	std::cout << "Tropical: " << fruit.tropical << std::endl;
	std::noboolalpha;
}
