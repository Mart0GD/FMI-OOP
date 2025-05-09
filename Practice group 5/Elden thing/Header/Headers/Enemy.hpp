#pragma once
#include "Player.hpp"
#include <iostream>

class Player;

class Enemy {

public:
	Enemy();
	Enemy(const char* name, int32_t hp, int32_t attackPower);

	Enemy(const Enemy& other);
	Enemy& operator=(const Enemy& other);

	~Enemy();

	const char* getName() const { return name; }
	int32_t getHp() const { return hp; }
	int32_t getMaxHp() const { return maxHp; }
	int32_t getAttackPower() const { return attackPower; }

	operator bool() const;

	void getDamage(uint32_t damage);
	void attack(Player& player, bool weak = false);

	void print();

private:
	static bool set(char*& where, const char* what);
	void die();

private:

	//base
	char* name;
	int32_t hp;
	int32_t maxHp;
	int32_t attackPower;
};

bool operator!(const Enemy& e);

std::ostream& operator << (std::ostream& os, const Enemy& e);

bool operator < (const Enemy& enemy, const Player& player);
bool operator <= (const Enemy& enemy, const Player& player);

bool operator > (const Enemy& enemy, const Player& player);
bool operator >= (const Enemy& enemy, const Player& player);

bool operator == (const Enemy& enemy, const Player& player);
bool operator != (const Enemy& enemy, const Player& player);