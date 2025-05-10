#pragma once
#include <iostream>
#include "Point.hpp"

enum Weapon {
	Sword,
	Wand,
	Staff,
	Axe,
	COUNT
};

const char weaponStr[COUNT][10] = { "Sword", "Wand", "Staff", "Axe" };

class Player {

public:
	Player(int32_t hp, const char* name, const Point& position, Weapon weapon, int32_t ad);

	Player(const Player& other);
	Player& operator=(const Player& other);

	Player(Player&& other) noexcept;
	Player& operator=(Player&& other) noexcept;

	virtual ~Player() noexcept;

	void move(const Point& newPos) { position = newPos; }

	virtual void handleAttack(int32_t damage);
	virtual bool attack(Player* const other);

	virtual void print() const;

public:
	virtual Player* clone() const = 0;

protected:
	char* copy(const char* what);

private:
	void clear();

public:

	int32_t getHp() const { return hp; }
	const char* getName() const { return name; }
	Point getPosition() const { return position; }
	Weapon getWeapon() const { return weapon; }
	int32_t getAttackPower() const { return attackDamage; }
	bool alive() const { return hp > 0; }


protected:
	
	int32_t hp;
	const char* name;
	Point position;
	Weapon weapon;
	int32_t attackDamage;
};