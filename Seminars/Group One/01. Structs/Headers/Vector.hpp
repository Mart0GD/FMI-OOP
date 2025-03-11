#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP
/*
«адача 1. ƒа се дефинира тип структура Vector, който определ€ вектор в тримерното пространство
и да се реализират функции за:
а) създаване на вектор;
б) извеждане на вектор на екрана;
в) намиране на сумата на два вектора;
г) намиране на разликата на два вектора;
д) намиране на произведението на вектор с число;
е) намиране на скаларното произведение на два вектора;
ƒа се напише програма, ко€то създава н€колко вектора и намира и извежда сумата, разликата и различните произведени€ на векторите.
*/

struct Vector {
	double x;
	double y;
	double z;
};

Vector CreateVector();
void PrintVector(const Vector& v);
Vector SumVectors(const Vector& v1, const Vector& v2);
Vector SubtractVectors(const Vector& v1, const Vector& v2);
Vector MultiplyVecotrWithScalar(const Vector& v1, double scalar);
double DotProduct(const Vector& v1, const Vector& v2);

#endif