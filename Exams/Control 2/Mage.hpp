#pragma once
#include "Player.hpp"

class Mage: public Player {

public:

	Mage(int32_t hp, const char* name, const Point& position, Weapon weapon, int32_t ad, 
		const char* specialAbility, float coefficient);

	Mage(const Mage& other);
	Mage& operator=(const Mage& other);

	Mage(Mage&& other) noexcept;
	Mage& operator=(Mage&& other) noexcept;

	virtual ~Mage() noexcept override;

	virtual bool attack(Player* const other) override;

	virtual void print() const override;

public:
	virtual Player* clone() const override;

public:
	const char* getSpecialAbility() const { return specialAbility; }
	float getCoefficient() const { return coefficient; }

private:
	void clear();

protected:
	char* specialAbility;
	float coefficient;
};