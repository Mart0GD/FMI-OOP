#include "Player.hpp"
#include "Enemy.hpp"
#include "PlayerConfig.hpp"
#include "Weapon.hpp"

#pragma warning(disable:4996)

Player::Player()
	: Player(PlayerConfig{ "N/a", 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0 }) { }
Player::Player(const PlayerConfig& config)
	: flaskChargesHp(START_FLASKS_COUNT), flaskChargesMp(START_FLASKS_COUNT), level(START_LEVEL)
{
	this->name = strcpy(new char[strlen(config.name) + 1], config.name);

	this->hp = maxHp = config.hp;
	this->mp = maxMp = config.mp;
	this->stamina = maxStamina = config.stamina;
	this->currentWeight = 0;
	this->runes = config.runes;
	this->maxCarryCapacity = config.maxCarryCapacity;

	weaponSlots = new(std::nothrow) Weapon * [MAX_WEAPON_SLOTS] {};
	if (!weaponSlots) {
		delete[] name;
		throw std::bad_alloc();
	}
	for (int i = 0; i < MAX_WEAPON_SLOTS; i++) weaponSlots[i] = nullptr;
	currentWeaponSlot = 0;

	//spells
	this->strength = config.strength;
	this->dexterity = config.dexterity;
	this->intelligence = config.intelligence;
	this->faith = config.faith;
	this->endurance = config.endurance;

	spellSlots = new(std::nothrow) Spell * [MAX_SPELL_SLOTS] {};
	if (!spellSlots) {
		delete[] weaponSlots; delete[] name;
		throw std::bad_alloc();
	}
	for (int i = 0; i < MAX_SPELL_SLOTS; i++) spellSlots[i] = nullptr;
	equippedSpellIndex = 0;
}

Player::Player(const Player& other) 
	: Player(PlayerConfig
			{ other.name, other.hp, other.mp, other.stamina, other.runes, other.maxCarryCapacity,
			  other.strength, other.dexterity, other.intelligence, other.faith, other.endurance}) {
	
	for (int i = 0; i < MAX_WEAPON_SLOTS; i++){
		weaponSlots[i] = other.weaponSlots[i];
	}
	currentWeaponSlot = other.currentWeaponSlot;

	for (int i = 0; i < MAX_SPELL_SLOTS; i++) {
		spellSlots[i] = other.spellSlots[i];
	}
	equippedSpellIndex = other.equippedSpellIndex;

	flaskChargesHp = other.flaskChargesHp;
	flaskChargesMp = other.flaskChargesMp;
	level = other.level;

}
Player& Player::operator=(const Player& other) {
	if (this == &other) return *this;

	Player copy(other);
	*this = std::move(copy);

	return *this;
}

Player::Player(Player&& other) noexcept
	: Player(PlayerConfig
			{ other.name, other.hp, other.mp, other.stamina, other.runes, other.maxCarryCapacity,
			  other.strength, other.dexterity, other.intelligence, other.faith, other.endurance }) {
	name = other.name;
	weaponSlots = other.weaponSlots;
	spellSlots = other.spellSlots;

	other.weaponSlots = nullptr;
	other.spellSlots = nullptr;
	other.name = nullptr;

	this->equippedSpellIndex = other.equippedSpellIndex;
	this->currentWeaponSlot = other.currentWeaponSlot;

	this->flaskChargesHp = other.flaskChargesHp;
	this->flaskChargesMp = other.flaskChargesMp;
	this->level = other.level;
	

}
Player& Player::operator=(Player&& other) noexcept {
	if (this == &other) return *this;

	std::swap(name, other.name);
	std::swap(weaponSlots, other.weaponSlots);
	std::swap(spellSlots, other.spellSlots);

	this->hp = maxHp = other.hp;
	this->mp = maxMp = other.mp;
	this->stamina = maxStamina = other.stamina;
	this->currentWeight = other.currentWeight;
	this->runes = other.runes;
	this->maxCarryCapacity = other.maxCarryCapacity;

	this->strength = other.strength;
	this->dexterity = other.dexterity;
	this->intelligence = other.intelligence;
	this->faith = other.faith;
	this->endurance = other.endurance;

	this->flaskChargesHp = other.flaskChargesHp;
	this->flaskChargesMp = other.flaskChargesMp;
	this->level = other.level;

	return *this;
}

Player::~Player() noexcept {
	for (int i = 0; i < MAX_WEAPON_SLOTS; i++)
	{
		weaponSlots[i] = nullptr;
	}
	delete[] weaponSlots;

	for (int i = 0; i < MAX_SPELL_SLOTS; i++)
	{
		delete spellSlots[i];
	}
	delete[] spellSlots;
	delete[] name;
}

bool Player::getDamage(int32_t damage) {
	if (damage < 0) return false;

	std::cout << "\nPlayer damaged for " << damage << "hp!\n";
	if (hp - damage < 0) {
		hp = 0;
		die(); return false;
	}

	hp -= damage;
	return true;
}

bool Player::useHpFlask() {
	if (flaskChargesHp <= 0) {
		std::cout << "no flasks!";
		return false;
	}

	if (hp + FLASKS_HEAL_FACTOR > maxHp) hp = maxHp;
	else hp += FLASKS_HEAL_FACTOR;

	std::cout << "\nPlayer healed for " << FLASKS_HEAL_FACTOR << ". Hp are now --> " << hp << '\n';
	--flaskChargesHp;
	return true;
}
bool Player::useManaFlask() {
	if (flaskChargesMp <= 0) {
		std::cout << "No mana flasks!";
		return false;
	}

	if (mp + FLASKS_MANA_FACTOR > maxMp) mp = maxMp;
	else mp += FLASKS_MANA_FACTOR;

	std::cout << "\nPlayer mana healed for " << FLASKS_MANA_FACTOR << ". Mp are now --> " << mp << '\n';
	--flaskChargesMp;
	return true;
}

bool Player::getWeapon(Weapon& weapon) {
	if (weapon.getWeight() + currentWeight >= maxCarryCapacity) {
		std::cout << "!!Over encumbered!! Cannot pick up wepon!";
		return false;
	}
	if(weapon.getRequiredStrength() > level) {
		std::cout << "!!Low level!! Cannot pick up wepon!";
		return false;
	}

	int index = 0;
	while (index < MAX_WEAPON_SLOTS && weaponSlots[index]) {
		index++;
	}

	if (index == MAX_WEAPON_SLOTS) return false;
	weaponSlots[index] = &weapon;

	std::cout << "\nPlayer has gotten a new wepon \n";
	weapon.printInfo();
	return true;
}
bool Player::equipWeapon(uint32_t index) {
	if (index >= maxCarryCapacity) return false;

	currentWeaponSlot = index;

	std::cout << "\nCurrent wepon is \n";
	weaponSlots[index]->printInfo();
	return true;
}
bool Player::attack(Enemy& enemy) {
	if (!weaponSlots[currentWeaponSlot]) {
		std::cout << "No weapon equiped!";
		return false;
	}

	enemy.getDamage(getCurrentWeapon()->getDamage());
	std::cout << "Enemy hit for " << getCurrentWeapon()->getDamage() << " damage!!!!\n";
	return true;
}

void Player::die() {
	// for now
	std::cout << "player is dead!" << "\n\n";

}

bool Player::learnSpell(const Spell& spell, int32_t index) {
	if (spell.getRequiredFaith() > faith) {
		std::cout << "Spell faith to strong!\n";
		return false;
	}
	if (spell.getRequiredIntelligence() > intelligence) {
		std::cout << "Spell intelligence to high!\n";
		return false;
	}
	if (spellSlots[index]) {
		std::cout << "spell already equiped at this spot!";
		return false;
	}

	spellSlots[index] = new Spell(spell);
	return true;
}
bool Player::learnSpell(Spell&& spell, int32_t index) {
	if (spell.getRequiredFaith() > faith) {
		std::cout << "Spell faith to strong!\n";
		return false;
	}
	if (spell.getRequiredIntelligence() > intelligence) {
		std::cout << "Spell intelligence to high!\n";
		return false;
	}
	if (spellSlots[index]) {
		std::cout << "spell already equiped at this spot!";
		return false;
	}

	spellSlots[index] = new Spell(spell);
	return true;
}
bool Player::forgetSpell(int32_t index) {
	if (index < 0 || index > 2) {
		std::cout << "invalid index\n";
		return false;
	}
	delete[] spellSlots[index]; spellSlots[index] = nullptr;
	return true;
}
bool Player::setEquippedSpell(int32_t index) {
	if (index < 0 || index > 2 || !spellSlots[index]) {
		std::cout << "Invalid index!";
		return false;
	}
	equippedSpellIndex = index;
}
bool Player::castSpell(Enemy& enemy) {
	if (equippedSpellIndex < 0 || equippedSpellIndex > 2 || !spellSlots[equippedSpellIndex]) {
		std::cout << "No spell equiped!\n";
		return false;
	}
	Spell* spell = spellSlots[equippedSpellIndex];
	if (spell->getMpCost() > mp) {
		std::cout << "Not enough mana!\n";
		return false;
	}
	if (spell->isOnCooldown()) {
		std::cout << "Spell on cooldown!\n";
		return false;
	}

	enemy.getDamage(spell->getDamage());
	std::cout << "Player cast spell " << spell->getName() << '\n';
	spell->resetCooldown();
	mp -= spell->getMpCost();
	return true;
}
bool Player::castSpell() {
	if (equippedSpellIndex < 0 || equippedSpellIndex > 2 || !spellSlots[equippedSpellIndex]) {
		std::cout << "No spell equiped!";
		return false;
	}
	Spell* spell = spellSlots[equippedSpellIndex];
	if (spell->getMpCost() > mp) {
		std::cout << "Not enough mana!";
		return false;
	}
	if (spell->isOnCooldown()) {
		std::cout << "Spell on cooldown!";
		return false;
	}

	std::cout << "Player cast spell " << spell->getName();
	spell->resetCooldown();
	mp -= spell->getMpCost();
	return true;
}
void Player::decrementSpellCooldowns() {
	for (int i = 0; i < MAX_SPELL_SLOTS; i++){
		if (spellSlots[i] && spellSlots[i]->isOnCooldown()) {
			spellSlots[i]->decrementCooldown();
		}
	}
}

void Player::printSpells() {
	for (int i = 0; i < MAX_SPELL_SLOTS; i++)
	{
		if (spellSlots[i]) {
			spellSlots[i]->printInfo();
			std::cout << '\n';
		}
	}
}
bool Player::increaseStat(Stat stat, int32_t val) {
	switch (stat)
	{
		case HP:
			hp += val;
			break;
		case MP:
			mp += val;
			break;
		case STAMINA:
			stamina += val;
			break;
		case LEVEL:
			level += val;
			break;
		case MAX_CARRY_CAPACITY:
			maxCarryCapacity += val;
			break;
		case STRENGTH:
			strength += val;
			break;
		case DEXTERITY:
			dexterity += val;
			break;
		case INTELLIGENCE:
			intelligence += val;
			break;
		case FAITH:
			faith += val;
			break;
		case ENDURANCE:
			endurance += val;
			break;
		default:
			return false;
	}
	return true;
}

Player& Player::operator++() {
	++this->level;
	return *this;
}
Player Player::operator++(int) {
	Player copy(*this);
	++(*this);

	return copy;
}

Player operator+(const Player& p, Weapon& wp) {
	Player copy(p);

	copy += wp;
	return copy;
}
Player& Player::operator+=(Weapon& wp) {
	if (!getWeapon(wp)) throw std::invalid_argument("Cannot get weapon!");

	std::cout << "Successfully gained weapon " << wp.getName() << " Congrats!!";
	return *this;
}

Player operator-(const Player& p, Enemy& enemy) {
	Player copy(p);

	copy -= enemy;
	return copy;
}
Player& Player::operator-=(Enemy& enemy) {
	if (!attack(enemy)) throw std::invalid_argument("no weapon to attack with!!");
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
	if (!os) throw std::invalid_argument("bad stream!");

	std::cout << p.getName() << ' ' << p.getLevel() << ' ' << p.getHp() << ' ';
	Weapon* wp = p.getCurrentWeapon();
	if (wp) wp->printInfo();
	else std::cout << "no weapon equiped!";

	return os;
}

Player::operator bool() {
	return hp > 0;
}
bool Player::operator!() {
	return !((bool)*this);
}

