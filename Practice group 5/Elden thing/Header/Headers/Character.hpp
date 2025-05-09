#pragma once

#include <iostream>
#include "Spell.hpp"
#include "CharacterConfig.hpp"

class Character {

public:
	Character(const CharacterConfig& config);

	Character(const Character& config);
	Character& operator=(const Character& other);

	Character(Character&& other) noexcept;
	Character& operator=(Character&& other) noexcept;

	~Character() noexcept;

	void copyValues(const Character& other);

	bool useHpFlask();
	bool useMpFlask();
	void LevelUp();

	void takeDamage(int32_t damage);
	int32_t calculateAttackPower() const { return (level * 0.75) + strength; }
	int32_t calculateDefensePower() const { return (level * 0.75) + strength + dexterity; }

	void virtual performSpecialAction();
	bool virtual canLearnSpell(const Spell& spell) const;
	const virtual char* getClassName() const;

private:

	// characteristics
	char* name;
	int32_t hp, maxHp;
	int32_t mp, maxMp;
	int32_t stamina, maxStamina;
	int32_t runes;
	int32_t level;

	// base
	int32_t strength;
	int32_t intelligence;
	int32_t dexterity;
	int32_t faith;
	int32_t endurance;

	//resources
	int32_t flaskChargesHp;
	int32_t flaskChargesMp;
	bool isAlive;
	Spell** spellSlots;
	int32_t equippedSpellIndex;
};