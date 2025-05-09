#include "Weapon.hpp"
#pragma warning(disable:4996)

void Weapon::initialize(const char name[], int32_t damage, double weight, int32_t requiredStrength) {
	if (!name || !*name || strlen(name) >= maxNameSize) throw std::invalid_argument("Invalid name!");
	if(damage < 0 || weight < 0 || requiredStrength < 0) throw std::invalid_argument("negative value detected!");

	strcpy(this->name, name);

	this->damage = damage;
	this->weight = weight;
	this->requiredStrength = requiredStrength;
}

void Weapon::printInfo() {
	std::cout 
		<< this->name << ' ' 
		<< this->damage << ' ' 
		<< this->weight << ' ' 
		<< this->requiredStrength << std::endl;
}

bool operator == (const Weapon& w1, const Weapon& w2) {
	return strcmp(w1.getName(), w2.getName()) == 0 && w1.getDamage() == w2.getDamage();
}
bool operator != (const Weapon& w1, const Weapon& w2) {
	return !(w1 == w2);
}

bool operator > (const Weapon& w1, const Weapon& w2) {
	return w1.getDamage() > w2.getDamage();
}
bool operator >= (const Weapon& w1, const Weapon& w2) {
	return w1 > w2 || w1 == w2;
}

bool operator < (const Weapon& w1, const Weapon& w2) {
	return !(w1 > w2);
}
bool operator <= (const Weapon& w1, const Weapon& w2) {
	return w1 < w2 || w1 == w2;
}

std::istream& operator>>(std::istream& is, Weapon& w) {

	char buffer[1024];
	is.getline(buffer, sizeof(buffer), ' ');
	if (!is || !*buffer) throw std::invalid_argument("bad input!");

	int32_t damage;
	is >> damage;
	if(!is) throw std::invalid_argument("bad input!");

	double weight;
	is >> weight;
	if (!is) throw std::invalid_argument("bad input!");

	int32_t strength;
	is >> strength;
	if (!is) throw std::invalid_argument("bad input!");

	w.initialize(buffer, damage, weight, strength); // can throw 
	return is;
}
std::ostream& operator<<(std::ostream& os, const Weapon& w) {
	std::cout
		<< w.getName() << ' '
		<< w.getDamage() << ' '
		<< w.getWeight() << ' '
		<< w.getRequiredStrength() << '\n';
	return os;
}
