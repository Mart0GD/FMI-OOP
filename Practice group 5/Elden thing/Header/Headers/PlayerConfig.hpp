#pragma once

struct PlayerConfig {
	// main attributes
	const char* name{ nullptr };
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

};