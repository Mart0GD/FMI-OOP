#include "Necromancer.hpp"

Necromancer::Necromancer(int32_t hp, const char* name, const Point& position, Weapon weapon, int32_t ad,
	const char* specialAbility, float coefficient) 
	: Mage(hp, name, position , weapon, ad, specialAbility, coefficient)
{}

bool Necromancer::attack(Player* const other) {
	if(!Mage::attack(other)) return false;

	if (_collection.getPlayersCount() > 0) {
		int random = rand() % _collection.getPlayersCount();
		_collection.getPlayer(random)->attack(other);
	}

	if (!other->alive()) {
		_collection.addPlayer(*other->clone());
	}
}

void Necromancer::print() const {
	Mage::print();
	if (_collection.getPlayersCount() > 0) {
		std::cout << "\nCollection : \n";
		for (int i = 0; i < _collection.getPlayersCount(); i++) {
			_collection.getPlayer(i)->print();
			std::cout << '\n';
		}
	}
}

Player* Necromancer::clone() const {
	return new Necromancer(*this);
}