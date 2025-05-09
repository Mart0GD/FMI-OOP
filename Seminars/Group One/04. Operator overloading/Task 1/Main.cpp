#include "DynamicArray.hpp"

int main() {

	try
	{
		DynamicArray da1(10);
		DynamicArray da2(5);

		da2 += 2;
		da2 += 3;
		da2 += 8;

		da1 += 1;

		da2 = da1 + 2;
		da1 += da2;

		da2 += 1;
		da2 -= 1;

		da2[1] = 1;

		std::cin >> da1;
		std::cout << da1;

		/*da1 = da2;
		std::cout << (da1 == da2);*/

		for (int i : da1) {
			std::cout << i;
		}
		std::cout << da1;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}