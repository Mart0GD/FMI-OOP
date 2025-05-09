#pragma once
#include "Weapon.hpp"

namespace weapon_test {
	void valid() {

		Weapon sword;
		sword.initialize("Excalibur", 12, 0.2, 11);

		Weapon shovel;
		shovel.initialize("Big shovel", 20, 2, 40);

		std::cout << "\nFirst weapon info: " << '\n';
		sword.printInfo();

		std::cout << "\nSecond weapon info: " << '\n';
		shovel.printInfo();
	}

	void invalid() {

		std::cout << "\nfirst bad weapon\n";
		Weapon longNameSword;
		try
		{
			longNameSword.initialize("Excaliburrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr", 12, 0.2, 11);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		
		std::cout << "\second bad weapon\n";
		Weapon shovel;
		try
		{
			shovel.initialize("Big shovel", -1, -2, -40);
		}
		catch (const std::exception& e) 
		{
			std::cout << e.what() << '\n';
		}
		

	}
}