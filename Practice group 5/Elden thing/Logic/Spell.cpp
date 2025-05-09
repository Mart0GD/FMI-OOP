#include "Spell.hpp"
#pragma warning(disable:4996)

Spell::Spell()
	: Spell("N/a", 0, 0, 0, 0, 0) { }
Spell::Spell(const char* name, int32_t damage, int32_t mpCost,
			 int32_t coolodown, int32_t requiredIntelligence, int32_t requiredFaith) 
	:name(nullptr), requiredIntelligence(requiredIntelligence), requiredFaith(requiredFaith)
{
	if (damage < 0 || mpCost < 0 || coolodown < 0 || requiredIntelligence < 0 || requiredFaith < 0)
		throw std::invalid_argument("negative value!");
	if (!name || !*name)
		throw std::invalid_argument("null pointer!");

	this->name = strcpy(new char[strlen(name) + 1], name);

	this->damage = damage;
	this->mpCost = mpCost;
	this->coolodown = coolodown;
	this->remainingCooldown = 0;
}

Spell::Spell(const Spell& other) 
	: Spell(other.name, other.damage, other.mpCost, 
			other.coolodown, other.requiredIntelligence, other.requiredFaith) { }
Spell& Spell::operator=(const Spell& other) {
	if (this == &other) return *this;

	Spell copy(other);
	*this = std::move(copy);

	return *this;
}

Spell::Spell(Spell&& other) noexcept
	: requiredIntelligence(other.requiredIntelligence), requiredFaith(other.requiredFaith)
{
	name = other.name;
	damage = other.damage;
	mpCost = other.mpCost;
	coolodown = other.coolodown;
	remainingCooldown = 0;
	
	other.name = nullptr;
}
Spell& Spell::operator=(Spell&& other) noexcept {
	if (this == &other) return *this;

	std::swap(name, other.name);
	damage = other.damage;
	mpCost = other.mpCost;
	coolodown = other.coolodown;
	remainingCooldown = 0;

	return *this;
}

Spell::~Spell() noexcept{
	delete[] name; name = nullptr;
}

bool Spell::setName(const char* what) {
	if (!*what) return false;

	char* temp = new(std::nothrow) char[strlen(what) + 1];
	if (!temp) return false;
	strcpy(temp, what);

	delete[] name;
	name = temp;

	return true;
}

void Spell::resetCooldown() { remainingCooldown = coolodown; }
bool Spell::decrementCooldown() {
	if (remainingCooldown == 0) return false;
	--remainingCooldown; 
	return true;
}
bool Spell::isOnCooldown() const { return remainingCooldown > 0; }

std::ostream& operator << (std::ostream& os, const Spell& s) {
	std::cout
		<< s.getName() << ' '
		<< s.getDamage() << ' '
		<< s.getMpCost() << ' '
		<< s.getCooldown() << ' '
		<< s.getRequiredIntelligence() << ' '
		<< s.getRequiredFaith() << '\n';
	return os;
}

bool operator < (const Spell& s1, const Spell& s2) {
	return s1.getDamage() < s2.getDamage();
}
bool operator <= (const Spell& s1, const Spell& s2) {
	return s1 < s2 || s1 == s2;
}

bool operator > (const Spell& s1, const Spell& s2) {
	return !(s1 < s2);
}
bool operator >= (const Spell& s1, const Spell& s2) {
	return s1 > s2 || s1 == s2;
}

bool operator == (const Spell& s1, const Spell& s2) {
	return strcmp(s1.getName(), s2.getName()) == 0 && s1.getDamage() == s2.getDamage();
}
bool operator != (const Spell& s1, const Spell& s2) {
	return !(s1 == s2);
}
