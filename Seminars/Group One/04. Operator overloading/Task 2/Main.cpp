#include "BoolArray.hpp"

int main() {
	BoolArray arr;

	arr[0] = 1;
	arr = 255;

	std::cout << (uint32_t)arr << '\n';

	arr += 1;
	arr += 0;

	BoolArray arr2;

	arr2 = 15;

	std::cout << '\n' << arr2;
	std::cout << '\n' << arr;
	arr += arr2;
	std::cout << '\n' << arr;

	
	std::cout <<'\n' << arr;

	std::cout << '\n';
	for (bool i : arr)
	{
		std::cout << i << ' ';
	}
}