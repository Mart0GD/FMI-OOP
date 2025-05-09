#pragma once

#include "Player.hpp"
#include "Enemy.hpp"
#include "Weapon.hpp"
#include "Spell.hpp"
#include "PlayerConfig.hpp"

class GameManager {

public:

	static GameManager& getInstance();
	static void releaseInstance();

	static void startGame();
	static void playerAttack(Player& player, Enemy& enemy);
	static void enemyAttack(Enemy& enemy, Player& player);
	static void displayStatus(const Player& player, const Enemy& enemy);

	static GameManager* instance;

private:
	GameManager() {};
	GameManager(const GameManager& other) = delete;
	GameManager& operator=(const GameManager& other) = delete;
	~GameManager() {};


};