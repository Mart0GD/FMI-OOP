#pragma once

struct CharacterConfig {
	const char* name;
	int32_t maxHp;
	int32_t maxMp;
	int32_t maxStamina;
	int32_t runes;

	// base
	int32_t strength;
	int32_t intelligence;
	int32_t dexterity;
	int32_t faith;
	int32_t endurance;
};