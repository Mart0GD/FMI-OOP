#include "Mage.hpp"
#pragma warning(disable:4996)

Mage::Mage(int32_t hp, const char* name, const Point& position, Weapon weapon, int32_t ad, 
	const char* specialAbility, float coefficient) 
	: Player(hp, name, position, weapon, ad), 
	  specialAbility(copy(specialAbility)), coefficient(coefficient)
{
	if (!this->specialAbility) throw std::invalid_argument("bad special ability argument!");
	if (coefficient < 0 || coefficient > 1) {
		clear();
		throw std::invalid_argument("invalid coefficient range!");
	}
}

Mage::Mage(const Mage& other) 
	:Player(other), coefficient(other.coefficient)
{
	specialAbility = strcpy(new char[strlen(other.specialAbility) + 1], other.specialAbility); // this is valid
}
Mage& Mage::operator=(const Mage & other) {
	if (this == &other) return *this;

	Player::operator=(other);
	specialAbility = strcpy(new char[strlen(other.specialAbility) + 1], other.specialAbility); // this is valid
	coefficient = other.coefficient;

	return *this;
}

Mage::Mage(Mage&& other) noexcept 
	:Player(other), specialAbility(other.specialAbility), coefficient(other.coefficient)
{
	other.specialAbility = nullptr;
}
Mage& Mage::operator=(Mage&& other) noexcept {
	if (this == &other) return *this;

	Player::operator=(other);
	std::swap(specialAbility, other.specialAbility);
	coefficient = other.coefficient;

	return *this;
}

Mage::~Mage() noexcept {
	clear();
}

bool Mage::attack(Player* const other) {
	if (!Player::attack(other)) return false;

	other->handleAttack(coefficient * 100); // знам че е прди атака ама чека за разстояние е горе
}

void Mage::print() const {
	Player::print();
	std::cout
		<< specialAbility << ' '
		<< coefficient << ' ';
}
Player* Mage::clone() const {
	return new Mage(*this);
}
void Mage::clear(){
	delete specialAbility;
}


