#include "Player.hpp"
#include "Enemy.hpp"

namespace enemy_test {
	void valid() {

		std::cout << "Creating pesho!\n";
		Enemy pesho("pesho", 100000000, 999);
		pesho.print();

		std::cout << "Creating gencho!\n";
		PlayerConfig config{ "pesho", 10, 10, 20, 110, 10, 50, 20, 10, 5, 10 };
		Player gencho(config);

		std::cout << "Pesho attacks gencho!\n";
		pesho.attack(gencho);
	}

	void invalid() {

		try
		{
			std::cout << "Trying to create pesho!\n";
			Enemy pesho("pesho", -100000000, 999);
			pesho.print();

		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		
		try
		{
			std::cout << "Trying to create pesho second time!!!!\n";
			Enemy pesho(nullptr, 100000000, 999);
			pesho.print();

		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}
}