#include "PlayerCollection.hpp"

#include "Mage.hpp"
#include "Warrior.hpp"
#include "Necromancer.hpp"
#include "Point.hpp"

int main() {

	PlayerCollection collection = PlayerCollection();

	Mage ivan(70, "ivan", { 1, 1 }, Staff, 10, "Swirl", 0.1);
	Warrior pesho(120, "pesho", { 10, 2 }, Axe, 30, 10);
	Necromancer gencho( 90, "gencho", { -2, -4 }, Wand, 70, "Tornado", 0.2);

	collection.addPlayer(ivan);
	collection.addPlayer(pesho);
	collection.addPlayer(gencho);

	for (int i = 0; i < collection.getPlayersCount() - 1; i++){
		Player* current = collection.getPlayer(i);
		for (int j = i + 1; j < collection.getPlayersCount(); j++){
			Player* attacked = collection.getPlayer(j);

			if (!current->attack(attacked)) {

				current->move({ attacked->getPosition().x - 1, attacked->getPosition().y - 1 });

				current->attack(attacked);
				attacked->attack(current);
			}
			else attacked->attack(current);


			if (!current->alive()) {
				collection.removePlayer(current->getName());
				--i;--j;
				break;
			}
			else if (!attacked->alive()) {
				collection.removePlayer(attacked->getName());
				--i;--j;
				break;
			}
		}
	}

	for (int i = 0; i < collection.getPlayersCount(); i++)
	{
		std::cout << "\nPlayer " << i + 1 << '\n';
		collection.getPlayer(i)->print();
		std::cout << '\n';
	}

	return 0;
}