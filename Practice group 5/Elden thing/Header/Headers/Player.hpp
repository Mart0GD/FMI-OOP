#pragma once

#include "Weapon.hpp"
#include "Spell.hpp"
#include "Enemy.hpp"
#include "PlayerConfig.hpp"
#include <iostream>

constexpr uint32_t MAX_WEAPON_SLOTS{ 3 };
constexpr uint32_t MAX_SPELL_SLOTS{ 3 };

constexpr uint32_t START_FLASKS_COUNT{ 3 };
constexpr uint32_t FLASKS_HEAL_FACTOR{ 20 };
constexpr uint32_t FLASKS_MANA_FACTOR{ 30 };

constexpr uint32_t START_LEVEL{ 0 };

class Enemy;

enum Stat {
	HP,
	MP,
	STAMINA,
	LEVEL,
	MAX_CARRY_CAPACITY,
	STRENGTH,
	DEXTERITY,
	INTELLIGENCE,
	FAITH,
	ENDURANCE
} ;

class Player {

public:
	Player();
	Player(const PlayerConfig& config);

	Player(const Player& other);
	Player& operator=(const Player& other);

	Player(Player&& other) noexcept;
	Player& operator=(Player&& other) noexcept;

	~Player() noexcept;

	#pragma region Getters

		const char* getName() const {return name;}
		int32_t getHp() const { return hp; }
		int32_t getMaxHp() const { return maxHp; }

		int32_t getMp() const { return mp; }
		int32_t getMaxMp() const { return maxMp; }

		int32_t getStamina() const { return stamina; }
		int32_t getMaxStamina() const { return maxStamina; }

		uint32_t getRunes() const { return runes; }
		uint32_t getLevel() const { return level; }

		uint32_t getflaskChargesHp() const { return flaskChargesHp; }
		uint32_t getflaskChargesMp() const { return flaskChargesMp; }

		double getCurrentWeight() const { return currentWeight; }
		double getMaxCarryCapacity() const { return maxCarryCapacity; }

		int32_t getStrength() const { return strength; }
		int32_t getDexterity() const { return dexterity; }
		int32_t getIntelligence() const { return intelligence; }
		int32_t getFaith() const { return faith; }
		int32_t getEndurance() const { return faith; }

		Weapon* getCurrentWeapon() const { return weaponSlots[currentWeaponSlot]; }

	#pragma endregion

	bool getDamage(int32_t damage);
	bool useHpFlask();
	bool useManaFlask();

	bool getWeapon(Weapon& weapon);
	bool equipWeapon(uint32_t index);
	bool attack(Enemy& enemy);

	bool learnSpell(const Spell& spell, int32_t index);
	bool learnSpell(Spell&& spell, int32_t index);
	bool forgetSpell(int32_t index);
	bool setEquippedSpell(int32_t index);
	bool castSpell(Enemy& enemy);
	bool castSpell();
	void decrementSpellCooldowns();

	void printSpells();
	bool increaseStat(Stat stat, int32_t val);

	Player& operator++();
	Player operator++(int);

	operator bool();
	bool operator!();

	Player& operator+=(Weapon& wp);
	Player& operator-=(Enemy& enemy);

private:
	void die();

private:

	// main attributes
	char* name;
	int32_t hp, maxHp;
	int32_t mp, maxMp;
	int32_t stamina, maxStamina;
	uint32_t runes;
	uint32_t level;

	// resources
	uint32_t flaskChargesHp;
	uint32_t flaskChargesMp;

	//equipment
	double currentWeight;
	double maxCarryCapacity;
	Weapon** weaponSlots;
	uint32_t currentWeaponSlot : 2;

	// new bactch of logic (spells)
	int32_t strength;
	int32_t dexterity;
	int32_t intelligence;
	int32_t faith;
	int32_t endurance;

	Spell** spellSlots;
	int32_t equippedSpellIndex : 2;
};

Player operator+(const Player& p, Weapon& wp);
std::ostream& operator<<(std::ostream& os, const Player& p);
