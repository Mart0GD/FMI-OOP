#include <iostream>

#include "Card.hpp"

constexpr std::size_t fileNameArgsIndex{ 1 };

int main3(int argc, char* args[]) {
	char* fileName = args[fileNameArgsIndex];

	char ch; 
	char cmd = ' ';
	std::cout << "Enter command --> ";

	std::size_t deckIndex = -1;
	bool res = false;
	Card card;
	while (std::cin >> ch >> cmd) {
		switch (cmd)
		{
			case 'a':
				card = {};
				res = readCard(card);
				if (!res) break;

				std::cout << "Enter deck index --> ";
				std::cin >> deckIndex;
				if (deckIndex < 0) break;

				addCardToBF(card, fileName, deckIndex);
			break;

			case 'c':
				readCard(card);

				std::cout << "Enter deck index --> ";
				std::cin >> deckIndex;
				if (deckIndex < 0) break;

				swapCardInBF(card, deckIndex, fileName);
			break;

			case 'p':
				std::cout << "Enter deck index --> ";
				std::cin >> deckIndex;

				getCardFromBF(card, fileName, deckIndex, false);
				printCard(card);
			break;

			case 'd':
				printAllCardsFromBF(fileName);
			break;

			case 'r':
				std:: cout << "enter deck index --> ";
				std::cin >> deckIndex;

				removeCardFromBF(fileName, deckIndex);
			break;

			case 'e': return 0;

			default: break;
		}
		card = {};
		std::cout << "Enter command --> ";
	}
	return 0;
}