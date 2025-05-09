#include "Vector3D.h"
#include <iostream>
#include <cmath>

double Length(const Vector3D& V) {
	return sqrt((V.x * V.x) + (V.y * V.y) + (V.z * V.z));
}

double DotProduct(const Vector3D& V1, const Vector3D& V2) {
	return (V1.x * V2.x) + (V1.y * V2.y) + (V1.z * V2.z);
}

Vector3D CrossProduct(const Vector3D& V1, const Vector3D& V2) {
	double x = (V1.y * V2.z) - (V2.y * V1.z);
	double y = (V1.z * V2.x) - (V2.z * V1.x);
	double z = (V1.x * V2.y) - (V2.x * V1.y);

	Vector3D crossProduct{ x, y, z };
	return crossProduct;
}

double Triple(const Vector3D& V1, const Vector3D& V2, const Vector3D& V3) {
	return DotProduct(V1, CrossProduct(V2, V3));
}

void MultiplyByScalar(Vector3D& V, double scalar) {
	V.x *= scalar; V.y *= scalar; V.z *= scalar;
}

void NormalizeVector(Vector3D& V) {
	MultiplyByScalar(V, 1.0 / Length(V));
}

Vector3D GetNegative(const Vector3D& V) {
	Vector3D opposite = { -V.x, -V.y, -V.z };
	return opposite;
}

Vector3D Sum(const Vector3D& V1, const Vector3D& V2) {
	Vector3D sum = { V1.x + V2.x, V1.y + V2.y , V1.z + V2.z };
	return sum;
}

Vector3D Difference(const Vector3D& V1, const Vector3D& V2) {
	return Sum(V1, GetNegative(V2));
}

void Print(const Vector3D& V) {
	std::cout << '(' << V.x << ',' << V.y << ',' << V.z << ')' << std::endl;
}