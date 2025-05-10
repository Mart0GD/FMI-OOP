#include "Warrior.hpp"

Warrior::Warrior(int32_t hp, const char* name, const Point& position, Weapon weapon, 
	int32_t ad, int32_t armor) 
	: Player(hp, name, position, weapon, ad), armor(armor) { }

void Warrior::handleAttack(int32_t damage) {
	if (armor > 0) {
		if (armor - damage < 0) {
			int rest = abs(armor - damage);
			hp -= rest;
			armor = 0;
			return;
		}
		armor -= damage;
	}
	else Player::handleAttack(damage);
}
void Warrior::print() const {
	Player::print();
	std::cout << armor << ' ';
}

Player* Warrior::clone() const {
	return new Warrior(*this);
}