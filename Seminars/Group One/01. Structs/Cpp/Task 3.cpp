#include <iostream>
#include "Fruit.hpp"

#pragma warning(disable : 4996)

int main3() {
	int n = 0;
	std::cin >> n;

	Fruit* fruits = new(std::nothrow) Fruit[n];
	if (!fruits) return -1;

	for (int i = 0; i < n; i++) {
		fruits[i] = CreateFruit();
	}

	SortFruits(fruits, n);
	std::cout << "---------------------------------" << std::endl;
	for (int i = 0; i < n; i++) {
		PrintFruit(fruits[i]);
	}

	std::cout << "---------------------------------" << std::endl;
	PrintTropicalPerennialFruit(fruits, n, Red);

	delete[] fruits;
	fruits = nullptr;
	return 0;
}


