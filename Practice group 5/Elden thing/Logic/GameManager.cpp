#include "GameManager.hpp"

GameManager& GameManager::getInstance() {
	if (!instance) instance = new GameManager();
	return *instance;
}
void GameManager::releaseInstance() {
	delete instance; instance = nullptr;
}

void GameManager::startGame() {
	PlayerConfig config{"gosho", 120, 45, 50, 110, 50, 10, 15, 20, 10, 15};
	Player gosho(config);

	Enemy pesho("pesho", 80, 9);

	Weapon dagger;
	dagger.initialize("demonic", 10, 4, 2);

	Weapon ak47;
	ak47.initialize("russian boy", 40, 25, 4);

	Spell swirl("swirl", 15, 20, 3, 10, 14);
	Spell fireball("fireball", 40, 25, 5, 10, 10);

	std::cout << "Our player gosho --> " << gosho << '\n';
	std::cout << "Enemy to the state PESHO!! --> " << pesho << '\n';

	std::cout << "Gosho get armed!!\n";
	try { gosho += ak47; }
	catch(std::exception& e){
		std::cout << e.what();

		std::cout << "Gosho is dumb ;D. But we'll teach him\n";
		for (size_t i = 0; i < 4; i++)
			++gosho;
	}


	try { gosho += ak47; }
	catch(...){
		std::cout << "Ok he is a lost cause";
		return;
	}

	std::cout << "Gosho will learn FIREBALL\n";
	if (!gosho.learnSpell(fireball, 0)) {
		std::cout << "I guess Gosho is very dumb ;D. But we'll teach him again!!!\n";
		for (int i = 0; i < 10; i++)
		{
			gosho.increaseStat(INTELLIGENCE, 1);
			gosho.increaseStat(FAITH, 1);
		}

		std::cout << "Gosho will try AGAIN to learn FIREBALL\n";
		if (!gosho.learnSpell(fireball, 0)) {
			std::cout << "Ok i give up ;D";
			return;
		}
	}

	

	gosho.equipWeapon(0);
	gosho.setEquippedSpell(0);
	// he is ready

	int iter = 0;
	while (pesho && gosho){
		playerAttack(gosho, pesho);

		if (iter % 3) enemyAttack(pesho, gosho);
		if (gosho.getMp() < 30 && gosho.getflaskChargesMp() > 0) gosho.useManaFlask();
		if (gosho.getHp() < 20 && gosho.getflaskChargesHp() > 0) gosho.useHpFlask();

		displayStatus(gosho, pesho);
		iter++;
	}

	if (!gosho) std::cout << "\nGAME LOST --> Gosho is dead );\n";
	else std::cout << "\nYOU WON --> Evil Pesho is dead (;!!!!!!!!\n";
}
void GameManager::playerAttack(Player& player, Enemy& enemy) {
	player.castSpell(enemy);
	player -= enemy;
	player.decrementSpellCooldowns();
}
void GameManager::enemyAttack(Enemy& enemy, Player& player) {
	if (enemy < player) enemy.attack(player, true);
	else enemy.attack(player, false);
}
void GameManager::displayStatus(const Player& player, const Enemy& enemy) {
	std::cout << "\n----------------------------\n";
	std::cout << "Player status --> " << player;
	std::cout << "Enemy sttaus --> " << enemy;
	std::cout << "\n----------------------------\n";
}

GameManager* GameManager::instance{ nullptr };