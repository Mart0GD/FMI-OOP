#pragma once
#include "Mage.hpp"
#include "PlayerCollection.hpp"


class Necromancer : public Mage{

public:

	Necromancer(int32_t hp, const char* name, const Point& position, Weapon weapon, int32_t ad,
		const char* specialAbility, float coefficient);

	virtual bool attack(Player* const other) override;

	virtual void print() const override;

public:
	virtual Player* clone() const override;

public:
	PlayerCollection collection() const { return _collection; }

private:
	PlayerCollection _collection;
};