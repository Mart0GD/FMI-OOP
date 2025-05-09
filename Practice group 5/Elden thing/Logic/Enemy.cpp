#include "Enemy.hpp"
#pragma warning(disable:4996)

Enemy::Enemy() 
	:Enemy("N/a", 0, 0/*, 0*/) { }
Enemy::Enemy(const char* name, int32_t hp, int32_t attackPower)
	:name(nullptr)
{
	if (hp < 0) throw std::invalid_argument("Negative value detected!");
	this->hp = hp;
	this->attackPower = attackPower;


	if (!set(this->name, name)) {
		throw std::invalid_argument("bad name!");
	}
}

Enemy::Enemy(const Enemy& other) 
	: Enemy(other.name, other.hp, other.attackPower) {}
Enemy& Enemy::operator=(const Enemy& other) {
	if (this == &other) return *this;

	hp = other.hp;
	attackPower = other.attackPower;

	if (!set(name, other.name)) {
		throw std::invalid_argument("bad name!");
	}
	return *this;
}

Enemy::~Enemy() {
	delete[] name; name = nullptr;
}

Enemy::operator bool() const {
	return hp > 0;
}

void Enemy::getDamage(uint32_t damage) {
	if (hp - damage <= 0) {
		std::cout << "Enemy is dead!";
		hp = 0;
		die();
		return;
	}

	hp -= damage;
	std::cout << "Enemy damaged for " << damage << " hitpoints! Health is now --> " << hp << "!\n";
}
void Enemy::attack(Player& player, bool weak) {
	if(weak) player.getDamage(attackPower/2);
	else player.getDamage(attackPower);
}
void Enemy::print() {
	std::cout << name << ' ' << hp << ' ' << attackPower << '\n';
}

bool Enemy::set(char*& where, const char* what) {
	if (!what || !*what) return false;

	char* temp = new(std::nothrow) char[strlen(what) + 1];
	if (!temp) return false;
	strcpy(temp, what);

	delete[] where;
	where = temp;
	return true;
}
void Enemy::die() {
	std::cout << "\nEnemy has died!\n";
}


bool operator!(const Enemy& e) {
	return !((bool)e);
}

std::ostream& operator << (std::ostream& os, const Enemy& e) {
	std::cout
		<< e.getName() << ' '
		<< e.getHp() << ' '
		<< e.getAttackPower();
	return os;
}

bool operator < (const Enemy& enemy, const Player& player) {
	if (!player.getCurrentWeapon()) return false;

	return enemy.getAttackPower() < player.getCurrentWeapon()->getDamage();
}
bool operator <= (const Enemy& enemy, const Player& player) {
	return enemy < player || enemy == player;
}

bool operator > (const Enemy& enemy, const Player& player) {
	return !(enemy < player);
}
bool operator >= (const Enemy& enemy, const Player& player) {
	return enemy > player || enemy == player;
}

bool operator == (const Enemy& enemy, const Player& player) {
	return enemy.getAttackPower() == player.getCurrentWeapon()->getDamage();
}
bool operator != (const Enemy& enemy, const Player& player) {
	return !(enemy == player);
}