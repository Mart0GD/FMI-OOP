#include "Player.hpp"
#pragma warning(disable:4996)

Player::Player(int32_t hp, const char* name, const Point& position, Weapon weapon, int32_t ad) 
	: hp(hp), name(copy(name)), position(position), weapon(weapon), attackDamage(ad) 
{
	if (!this->name) {
		throw std::invalid_argument("bad name!");
	}
	else if (hp < 0 || ad < 0) {
		clear();
		throw std::invalid_argument("negative value!");
	}
}

Player::Player(const Player& other) 
	:Player(other.hp, other.name, other.position, other.weapon, other.attackDamage) { }
Player& Player::operator=(const Player& other) {
	if (this == &other) return *this;

	/*clear();
	name = strcpy(new char[strlen(other.name) + 1], other.name);*/
	// we don't change the name

	hp = other.hp;
	position = other.position;
	weapon = other.weapon;
	attackDamage = other.attackDamage;

	return *this;
}

Player::Player(Player&& other) noexcept 
	: Player(other.hp, other.name, other.position, other.weapon, other.attackDamage){
	other.name = nullptr;
}
Player& Player::operator=(Player&& other) noexcept {
	if (this == &other) return *this;

	//std::swap(name, other.name); we don't change the name

	hp = other.hp;
	position = other.position;
	weapon = other.weapon;
	attackDamage = other.attackDamage;

	return *this;
}

Player::~Player() noexcept {
	clear();
}

void Player::handleAttack(int32_t damage) {
	if (hp - damage < 0) hp = 0;
	else hp -= damage;
}
bool Player::attack(Player* const other) {
	if (!inRange(position, other->position)) return false;

	other->handleAttack(this->getAttackPower());
}

void Player::print() const {
	std::cout
		<< hp << ' '
		<< name << ' '
		<< "( " << position.x << ',' << position.y << " )" << ' '
		<< weaponStr[(int)weapon] << ' '
		<< attackDamage << ' ';
}

char* Player::copy(const char* what) {
	if (!what || !*what) return nullptr;

	char* temp = new(std::nothrow) char[strlen(what) + 1];
	if (!temp) return nullptr;
	strcpy(temp, what);

	return temp;
}
void Player::clear() {
	delete[] name;
}

