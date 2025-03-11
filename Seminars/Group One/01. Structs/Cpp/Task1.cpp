#include <iostream>
#include "Vector.hpp"

int main1() {
	Vector v1 = CreateVector();
	Vector v2 = CreateVector();
	Vector v3 = CreateVector();

	std::cout << "Sum v1 and v2 --> "; PrintVector(SumVectors(v1, v2));
	std::cout << "Subtraction of v3 and v2 --> "; PrintVector(SubtractVectors(v3, v2));
	std::cout << "Sum v1 multiplied by 2 --> "; PrintVector(MultiplyVecotrWithScalar(v1, 2));
	std::cout << "Dot product v1 and v2 --> " << DotProduct(v1, v2);
	return 0;
}