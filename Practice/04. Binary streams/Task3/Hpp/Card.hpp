#pragma once
/*
Структура на карта:

боя -> един от следните низове: "clubs", "diamonds", "hearts", "spades"
символ -> един от следните символи: '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A'
*/

enum Paint {
	PUNKNOWN = -1,
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES,
	PCOUNT
};


struct Card {
	Paint paint{PUNKNOWN};
	uint32_t symb{0};
};

bool readCard(Card& card);
bool addCardToBF(const Card& card, const char* fileName, std::size_t deckIndex);
bool getCardFromBF(Card& card, const char* fileName, std::size_t deckIndex, bool ignoreMessage);
void printAllCardsFromBF(const char* fileName);
void printCard(const Card& card);
bool swapCardInBF(Card& card, std::size_t index, const char* fileName);
bool removeCardFromBF(const char* fileName, std::size_t deckIndex);