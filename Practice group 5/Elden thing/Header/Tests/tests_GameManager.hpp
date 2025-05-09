#pragma once

#include "GameManager.hpp"

namespace GameManager_test {
	void run() {
		GameManager::getInstance();

		GameManager* instance = GameManager::instance;

		instance->startGame();
		GameManager::releaseInstance();
	}
}