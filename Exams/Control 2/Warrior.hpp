#pragma once 
#include <iostream>
#include "Player.hpp"

class Warrior : public Player {

public:

	Warrior(int32_t hp, const char* name, const Point& position, Weapon weapon, int32_t ad, int32_t armor);

	virtual void handleAttack(int32_t damage) override;

	virtual void print() const;

public:
	virtual Player* clone() const override;

public:
	int32_t getArmor() const { return armor; }

private:
	int32_t armor;
};