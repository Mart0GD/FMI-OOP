#pragma once

#include <iostream>

constexpr int32_t maxNameSize{ 32 };

struct Weapon {

public:

	void initialize(const char name[], int32_t damage, double weight, int32_t requiredStrength);
	void printInfo();

	const char* getName() const { return name; }
	const int32_t getDamage() const { return damage; }
	const double getWeight() const { return weight; }
	const int32_t getRequiredStrength() const { return requiredStrength; }

private:

	char name[maxNameSize];
	int32_t damage;
	double weight;
	int32_t requiredStrength;

};

bool operator == (const Weapon& w1, const Weapon& w2);
bool operator != (const Weapon& w1, const Weapon& w2);

bool operator < (const Weapon& w1, const Weapon& w2);
bool operator <= (const Weapon& w1, const Weapon& w2);

bool operator > (const Weapon& w1, const Weapon& w2);
bool operator >= (const Weapon& w1, const Weapon& w2);

std::istream& operator>>(std::istream& is, Weapon& w);
std::ostream& operator<<(std::ostream& os, const Weapon& w);

