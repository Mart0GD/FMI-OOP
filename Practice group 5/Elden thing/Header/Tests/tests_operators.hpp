#pragma once

#include "Player.hpp"
#include "Enemy.hpp"
#include "Spell.hpp"
#include "Weapon.hpp"

namespace operators_tests {

	void inline player() {
		try
		{
			PlayerConfig p{ "pesho", 100, 20, 40, 150, 40, 10, 20, 10, 45, 10 };

			std::cout << "\nCreating pesho \n";
			Player pesho(p);
			std::cout << pesho;

			std::cout << "Creating dagger \n";
			Weapon dagger;
			dagger.initialize("killer", 10, 0.5, 1);
			dagger.printInfo();

			try
			{
				std::cout << "pesho tries to gets killer\n";
				pesho += dagger;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << '\n';
			}
			
			++pesho;

			try
			{
				std::cout << "pesho gets killer again\n";
				pesho += dagger;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << '\n';
			}

			pesho++;

			try
			{
				std::cout << "pesho gets killer again\n";
				pesho += dagger;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << '\n';
			}


			try
			{
				std::cout << "pesho gets killer again\n";
				pesho += dagger;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << '\n';
			}

			try
			{
				std::cout << "pesho will be full now!\n";
				pesho += dagger;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}

	void inline weapon() {
		Weapon w1;
		Weapon w2;

		std::cout << "\nReading weapon1 from console! --> ";
		std::cin >> w1;

		std::cout << "\nReading weapon2 from console! --> ";
		std::cin >> w2;

		std::cout << "\nWriting weapon1 to console! --> ";
		std::cout << w1;

		std::cout << "\nWriting weapon2 to console! --> ";
		std::cout << w2;

		std::cout << "\nw1 < w2?";
		bool res = w1 < w2;
		std::cout << "\nresult -> " << (res ? "Yes" : "No");


		std::cout << "\nw1 > w2?";
		res = w1 > w2;
		std::cout << "\nresult -> " << (res ? "Yes" : "No");


		std::cout << "\nw1 == w2?";
		res = w1 == w2;
		std::cout << "\nresult -> " << (res ? "Yes" : "No");


		std::cout << "\nw1 != w2?";
		res = w1 != w2;
		std::cout << "\nresult -> " << (res ? "Yes" : "No");
	}

	void inline enemy() {
		Enemy e("gencho", 10, 0);

		e.getDamage(10);

		std::cout << "Is Gencho alive? \n";
		std::cout << (e ? "Yes" : "No") << '\n';
		std::cout << (!e ? "No" : "Yes") << '\n';

		std::cout << "Printing Gencho --> " << e << '\n';
	}

	void inline spell() {
		Spell s1("Poison", 100, 45, 5, 20, 10);
		Spell s2("Frost", 50, 25, 2, 20, 10);

		std::cout << "\ns1 < s2?";
		bool res = s1 < s2;
		std::cout << "\nresult -> " << (res ? "Yes" : "No");


		std::cout << "\ns1 > s2?";
		res = s1 > s2;
		std::cout << "\nresult -> " << (res ? "Yes" : "No");


		std::cout << "\ns1 == s2?";
		res = s1 == s2;
		std::cout << "\nresult -> " << (res ? "Yes" : "No");

		std::cout << '\n' << s1;
		std::cout << s2;
	}

	void inline runAll() {
		player();
		weapon();
		enemy();
		spell();
	}
}