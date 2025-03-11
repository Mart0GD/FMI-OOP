#include "Vector.hpp"
#include <iostream>

Vector CreateVector() {
	double x_t, y_t, z_t;
	char c = ' ';
	do{
		std::cin >> x_t >> y_t >> z_t;
	} while (std::cin.fail());
	Vector v = { x_t, y_t, z_t };

	return v;
}

void PrintVector(const Vector& v) {
	std::cout << '(' << v.x << ',' << v.y << ',' << v.z << ')' << std::endl;
}

Vector SumVectors(const Vector& v1, const Vector& v2) {
	Vector vSum = {
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z,
	};
	return vSum;
}

Vector SubtractVectors(const Vector& v1, const Vector& v2) {
	Vector vSub = {
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z,
	};
	return vSub;
}

Vector MultiplyVecotrWithScalar(const Vector& v, double scalar) {
	Vector vScalar = {
		v.x * scalar,
		v.y * scalar,
		v.z * scalar
	};

	return vScalar;
}

double DotProduct(const Vector& v1, const Vector& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;;
}