#include <iostream>
#include "Vector3D.h"
#include "Box.h"

int main() {
	
	Vector3D v1 = { 1 , 1 , 1 };
	Vector3D v2 = { 1 , 2, 2 };
	Vector3D v3 = { 3 , 2 , 4 };

	std::cout << "vector 1 : "; Print(v1);
	std::cout << "vector 2 : "; Print(v2);
	std::cout << "vector 3 : "; Print(v3); 
	std::cout << std::endl;

	std::cout << "Length v1 : " << Length(v1) << std::endl;
	std::cout << "Dot product (v1 . v2): " << DotProduct(v1, v2) << std::endl;
	std::cout << "Cross product (v1 x v2): "; Print(CrossProduct(v1, v2));
	std::cout << "Tripple product ((v1 x v2).v3): " << Triple(v1, v2, v3) << std::endl;
	std::cout << "v1 mulptiplied by 3: "; MultiplyByScalar(v1, 3), Print(v1);
	std::cout << "v2 normalized: "; NormalizeVector(v2), Print(v2);
	std::cout << "v2 opposite: "; Print(GetNegative(v2));
	std::cout << "v1 + v2: "; Print(Sum(v1, v2));
	std::cout << "v1 - v2: "; Print(Difference(v1, v2));

	Vector3D box1VectorMin = { 0, 0, 0 };
	Vector3D box1VectorMax = { 0, 4, 0 };

	Vector3D box2VectorMin = { 0, 2, 0 };
	Vector3D box2VectorMax = { 2, 6, 3 };

	Box box1 = { box1VectorMin , box1VectorMax };
	Box box2 = { box2VectorMin , box2VectorMax };

	Print(GetCenter(box1));
	Print(GetExtent(box2));
	std::cout << IntersectBox(box1, box2);
	return 0;
}