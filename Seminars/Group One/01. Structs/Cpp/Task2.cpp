#include "Vector.hpp"
#include <iostream>

/*
Задача 2. Като се използва Vector (Задача 1), да се напише програма, която въвежда n вектора от тримерното пространство (n ≥ 3) и проверява дали съществуват три вектора от тях, които са взаимно перпендикулярни.
*/

int main2() {
	int n;
	std::cin >> n;

	Vector* vectors = new(std::nothrow) Vector[n];
	if (!vectors) return -1;

	for (int i = 0; i < n; i++){
		std::cout << "Enter vector --> ";
		vectors[i] = CreateVector();
	}

	int cnt = 0;
	bool hasThreeOrthogonal = 0;
	for (int i = 0; i < n; i++){
		cnt = 0;
		for (int j = i; j < n - 1; j++){
			if (DotProduct(vectors[j], vectors[j + 1]) == 0) cnt++;
		}
		if (cnt >= 2) {
			hasThreeOrthogonal = 1;
			break;
		}
	}

	std::cout << std::boolalpha;
	std::cout << hasThreeOrthogonal;

	delete[] vectors;
	vectors = nullptr;
	return 0;
}