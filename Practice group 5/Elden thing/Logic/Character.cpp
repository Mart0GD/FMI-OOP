#include "Character.hpp"
#pragma warning(disable:4996)

constexpr uint32_t START_FLASKS_COUNT{ 3 };
constexpr uint32_t FLASKS_HEAL_FACTOR{ 20 };
constexpr uint32_t FLASKS_MANA_FACTOR{ 30 };

constexpr uint32_t START_LEVEL{ 0 };
constexpr uint32_t MAX_SPELL_COUNT{ 3 };

Character::Character(const CharacterConfig& config) 
	: name(nullptr), flaskChargesHp(START_FLASKS_COUNT), flaskChargesMp(START_FLASKS_COUNT), 
	  level(0), equippedSpellIndex(0), isAlive(true)
{
	name = strcpy(new char[strlen(config.name) + 1], config.name);
	this->hp = this->maxHp = config.maxHp;
	this->mp = this->maxMp = config.maxMp;

	this->stamina = this->maxStamina = config.maxStamina;

	this->runes = config.runes;

	// base
	this->strength = config.strength;
	this->intelligence = config.intelligence;
	this->dexterity = config.dexterity;
	this->faith = config.faith;
	this->endurance = config.endurance;

	//resources
	spellSlots = new Spell * [MAX_SPELL_COUNT];
	if (!spellSlots) {
		delete[] name;
		throw std::bad_alloc();
	}
	for (int i = 0; i < MAX_SPELL_COUNT; ++i) spellSlots[i] = nullptr;
 }

Character::Character(const Character& other) 
{
	name = strcpy(new char[strlen(other.name) +1], other.name);
	copyValues(other);

	spellSlots = new(std::nothrow) Spell * [MAX_SPELL_COUNT];
	if (!spellSlots) {
		delete[] name;
		throw std::bad_alloc();
	}

	for (int i = 0; i < MAX_SPELL_COUNT; i++) 
		spellSlots[i] = other.spellSlots[i];
}
Character& Character::operator=(const Character& other) {
	if (this == &other) return *this;

	Character copy(other);
	*this = std::move(copy);

	return *this;
}

Character::Character(Character&& other) noexcept {
	name = other.name;
	spellSlots = other.spellSlots;

	copyValues(other);

	other.name = nullptr;
	other.spellSlots = nullptr;
}
Character& Character::operator=(Character&& other) noexcept  {
	if (this == &other) return *this;

	std::swap(name, other.name);
	std::swap(spellSlots, other.spellSlots);

	copyValues(other);

	return *this;
}

Character::~Character() noexcept {
	delete[] name;
	for (size_t i = 0; i < MAX_SPELL_COUNT; i++)
	{
		spellSlots[i] = nullptr;
	}
	delete[] spellSlots;
}

void Character::copyValues(const Character& other) {
	this->hp = other.hp;
	this->maxHp = other.maxHp;

	this->mp = other.mp;
	this->maxMp = other.maxMp;

	this->stamina = other.stamina;
	this->maxStamina = other.maxStamina;

	this->runes = other.runes;
	this->level = other.level;

	// base
	this->strength = other.strength;
	this->intelligence = other.intelligence;
	this->dexterity = other.dexterity;
	this->faith = other.faith;
	this->endurance = other.endurance;

	//resources
	this->flaskChargesHp = other.flaskChargesHp;
	this->flaskChargesMp = other.flaskChargesMp;
	this->isAlive = other.isAlive;
	this->equippedSpellIndex = other.equippedSpellIndex;
}

bool Character::useHpFlask() {
	if (flaskChargesHp == 0) return false;
	hp += FLASKS_HEAL_FACTOR;
	--flaskChargesHp;
}
bool Character::useMpFlask() {
	if (flaskChargesMp == 0) return false;
	mp += FLASKS_MANA_FACTOR;
	--flaskChargesMp;
}
void Character::LevelUp() { ++level; }

void Character::takeDamage(int32_t damage) {
	if (hp == 0) return;
	if (hp - damage < 0) {
		hp = 0; return;
	}

	hp -= damage;
}

void Character::performSpecialAction() {
	std::cout << "No special ability here!\n";
}
bool Character::canLearnSpell(const Spell& spell) const{
	return intelligence > spell.getRequiredIntelligence() && faith > spell.getRequiredFaith();
}
const char* Character::getClassName() const  {
	return "Character";
}

