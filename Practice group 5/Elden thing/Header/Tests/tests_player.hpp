#pragma once
#include "Player.hpp"
#include "Weapon.hpp"

// chat sheet 
/*
// 
	int32_t hp;
	int32_t mp;
	int32_t stamina;
	uint32_t runes;

	//equipment
	double maxCarryCapacity;

	// new bactch of logic (spells)
	int32_t strength;
	int32_t dexterity;
	int32_t intelligence;
	int32_t faith;
	int32_t endurance;
*/

namespace player_test {

	void basicTests() {

		try
		{
			Player gorgon({"pesho",10, 10, 20, 110, 10, 50, 20, 10, 5, 10});

			Weapon dagger;
			dagger.initialize("Excelcior", 4, 0.4, 0);

			gorgon.getWeapon(dagger);
			gorgon.equipWeapon(0);

			gorgon.getDamage(5);
			
			// overhealing
			gorgon.useHpFlask();
			gorgon.useHpFlask();
			gorgon.useHpFlask();

			gorgon.useManaFlask();

			Weapon heavyBaby;
			heavyBaby.initialize("big boy", 100, 100000, 999);

			gorgon.getWeapon(heavyBaby);
			gorgon.getDamage(11);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}
}