#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP
/*
������ 1. �� �� �������� ��� ��������� Vector, ����� �������� ������ � ���������� ������������
� �� �� ���������� ������� ��:
�) ��������� �� ������;
�) ��������� �� ������ �� ������;
�) �������� �� ������ �� ��� �������;
�) �������� �� ��������� �� ��� �������;
�) �������� �� �������������� �� ������ � �����;
�) �������� �� ���������� ������������ �� ��� �������;
�� �� ������ ��������, ����� ������� ������� ������� � ������ � ������� ������, ��������� � ���������� ������������ �� ���������.
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