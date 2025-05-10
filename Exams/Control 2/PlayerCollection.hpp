#pragma once
#include <iostream>
#include "Player.hpp"

constexpr int32_t startBuffer = 8;

class PlayerCollection {

public:
	PlayerCollection();

	PlayerCollection(const PlayerCollection& other);
	PlayerCollection& operator=(const PlayerCollection& other);

	PlayerCollection(PlayerCollection&& other) noexcept;
	PlayerCollection& operator=(PlayerCollection&& other) noexcept;

	~PlayerCollection() noexcept;

	bool addPlayer(const Player& player);
	
	Player* const getPlayer(int32_t index) const;
	Player* const getPlayer(const char* name) const;

	int32_t getPlayersCount() const { return count; }
	bool removePlayer(const char* name);

private:
	void clear();
	bool resize();

private:
	Player** collection;
	int32_t count, capacity;
};