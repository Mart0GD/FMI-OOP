#pragma once
#include <iostream>
class Spell {

public:
	Spell();
	Spell(const char* name, int32_t damage, int32_t mpCost, 
		  int32_t coolodown ,int32_t requiredIntelligence, int32_t requiredFaith);

	Spell(const Spell& other);
	Spell& operator=(const Spell& other);

	Spell(Spell&& other) noexcept;
	Spell& operator=(Spell&& other) noexcept;

	~Spell() noexcept;

	void resetCooldown();
	bool decrementCooldown();
	bool isOnCooldown() const;

	const char* getName() const { return name; }
	int32_t getDamage() const { return damage; }
	int32_t getMpCost() const { return mpCost; }
	int32_t getCooldown() const { return coolodown; }
	int32_t getRequiredIntelligence() const { return requiredIntelligence; }
	int32_t getRequiredFaith() const { return requiredFaith; }
	int32_t getRemainingCooldown() const { return remainingCooldown; }

	bool setName(const char* what);
	void printInfo() {
		std::cout << name << ' '
			<< damage << ' '
			<< mpCost << ' '
			<< coolodown << ' '
			<< requiredIntelligence << ' '
			<< requiredFaith << ' '
			<< remainingCooldown << ' ';
	}


private:

	char* name;
	int32_t damage;
	int32_t mpCost;
	int32_t coolodown;
	const int32_t requiredIntelligence;
	const int32_t requiredFaith;
	int32_t remainingCooldown;

};

std::ostream& operator << (std::ostream& os, const Spell& s);

bool operator < (const Spell& s1, const Spell& s2);
bool operator <= (const Spell& s1, const Spell& s2);

bool operator > (const Spell& s1, const Spell& s2);
bool operator >= (const Spell& s1, const Spell& s2);

bool operator == (const Spell& s1, const Spell& s2);
bool operator != (const Spell& s1, const Spell& s2);


