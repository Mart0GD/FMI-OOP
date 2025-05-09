#include "BoolArray.hpp"


int main() {

	try
	{
		BoolArray arr1 = BoolArray(3);
		BoolArray arr2 = BoolArray(3);

		//arr2 = arr1; test

		for (size_t i = 0; i < 8; i++)
		{
			arr1 += true;
		}

		std::cout << (uint32_t)arr1 << std::endl; // 255 representation 2^8 - 1

		std::cin >> arr2; // 10010101000000011 --> 76291
		std::cout << arr2[0] << std::endl;
		std::cout << (uint32_t)arr2 << std::endl; // 76291

		for (auto i : arr2) {
			std::cout << i;
		}
		std::cout << std::endl;
		 
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	
	return 0;
}