#pragma once

struct Vector3D {
	double x;
	double y;
	double z;
};

double Length(const Vector3D& V);
double DotProduct(const Vector3D& V1, const Vector3D& V2);
double Triple(const Vector3D& V1, const Vector3D& V2, const Vector3D& V3);
Vector3D CrossProduct(const Vector3D& V1, const Vector3D& V2);
Vector3D GetNegative(const Vector3D& V);
Vector3D Sum(const Vector3D& V1, const Vector3D& V2);
Vector3D Difference(const Vector3D& V1, const Vector3D& V2);
void MultiplyByScalar(Vector3D& V, double scalar);
void NormalizeVector(Vector3D& V);
void Print(const Vector3D& V);