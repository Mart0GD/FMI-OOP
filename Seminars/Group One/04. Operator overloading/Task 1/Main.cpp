#include "DynamicArray.hpp"

int main() {
	DynamicArray arr;

	for (int i = 0; i < 31; i++){
		arr += 3;
	}
	arr += 3; // resizing
	
	arr -= 3;
	std::cout << arr[0];

	arr += 1;
	std::cout << arr(1);
	arr += 2; arr += 3;

	std::cout << arr;
	std::cin >> arr;

	arr[0] = 2;
	arr[0] = arr[0] - 1;
	std::cout << arr[0];
}