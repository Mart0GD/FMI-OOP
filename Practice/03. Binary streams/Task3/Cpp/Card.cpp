#include <iostream>
#include <fstream>

#include "Card.hpp"
#pragma warning(disable: 4996)

#define PAINTS 4
#define SYMBOLS 13

constexpr std::size_t cardsCount{52};
constexpr std::size_t READ_BUFFER { 1024 };
constexpr const char paints[PCOUNT][9] = { "clubs", "diamonds", "hearts", "spades"};
constexpr const char symbols[13][3] = { "2", "3","4","5","6","7","8","9","10","Q","K","J","A" };

bool AreValid(char* paint, char* symbol) {
	bool validP = false;
	bool validS = false;
	for (int i = 0; i < PAINTS; i++){
		if (strcmp(paints[i], paint) == 0){
			validP = true;
			break;
		}
	}

	for (int i = 0; i < SYMBOLS; i++){
		if (strcmp(symbols[i], symbol) == 0){
			validS = true;
			break;
		}
	}

	return validP && validS;
}

char* readString(int size) {
	char* str = new(std::nothrow) char[size] {};
	if (!str) return NULL;

	do
	{
		std::cin.getline(str, size);
	} while (!str[0]);

	int newLen = strlen(str);
	char* temp = new(std::nothrow) char[newLen + 1];
	if (!temp) return NULL;

	strcpy(temp, str);
	delete[] str;
	str = temp;

	return str;
}

bool readCard(Card& card) {
	std::cout << "Enter card paint --> ";
	char* paint = readString(READ_BUFFER);
	if (!paint) return false;

	std::cout << "Enter card symbol --> ";
	char* symbol = readString(READ_BUFFER);
	if (!symbol) return false;
	
	if (!AreValid(paint, symbol)) {
		std::cout << "Invalid card!" << std::endl;
		readCard(card);
	}

	int enumIndex = -1;
	for (int i = 0; i < PCOUNT; i++){
		if (strcmp(paints[i], paint) == 0) enumIndex = i;
	}
	card.paint = (Paint)enumIndex;

	if (symbol[0] >= '0' && symbol[0] <= '9') card.symb = atoi(symbol);
	else card.symb = (unsigned)symbol[0];

	return true;
}

bool addCardToBF(const Card& card, const char* fileName, std::size_t deckIndex){
	if (deckIndex >= cardsCount || deckIndex < 0) return false;

	std::ofstream deck(fileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!deck.is_open()) {
		std::cerr << "Cannot open file for writing!";
		return false;
	}

	std::size_t cardSize = sizeof(card);
	deck.seekp(cardSize * deckIndex, std::ios::beg);
	deck.write(reinterpret_cast<const char*>(&card), cardSize);

	if (!deck) return false;
	deck.close();

}

void printCard(const Card& card) {
	if (card.symb == 0) return;

	if (card.symb > 10)  std::cout << (char)card.symb << ' ' << paints[(int)card.paint] << std::endl;
	else {
		std::cout
			<< card.symb << ' '
			<< paints[(int)card.paint]
			<< std::endl;
	}
}

bool getCardFromBF(Card& card, const char* fileName, std::size_t deckIndex, bool ignoreMessage) {
	if (deckIndex >= cardsCount || deckIndex < 0) return false;

	std::ifstream deck(fileName, std::ios::binary);
	if (!deck.is_open()) {
		std::cerr << "Cannot open file for reading!";
		return false;
	}

	Card tempCard = {PUNKNOWN, 0};
	std::size_t cardSize = sizeof(tempCard);
	deck.seekg(deckIndex * cardSize, std::ios::beg);
	deck.read(reinterpret_cast<char*>(&tempCard), cardSize);

	if (tempCard.paint == -1 || tempCard.symb == 0) {
		if(!ignoreMessage) std::cout << "No card at this index!" << std::endl;
		return false;
	}

	card = tempCard;
	deck.close();
	return true;
}

void printAllCardsFromBF(const char* fileName) {
	Card card = {};
	for (int i = 0; i < cardsCount; i++){
		getCardFromBF(card, fileName, i, true);
		if (card.symb != 0) {
			printCard(card);
			card = {};
		}

	}
}

bool swapCardInBF(Card& card, std::size_t index, const char* fileName) {
	if (index > cardsCount || index < 0) return false;

	std::fstream deck(fileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!deck.is_open()) {
		std::cerr << "Cannot open file for writing!";
		return false;
	}

	Card oldCard = { PUNKNOWN, 0 };
	std::size_t cardSize = sizeof(card);
	deck.seekg(cardSize * index, std::ios::beg);
	deck.read(reinterpret_cast<char*>(&oldCard), cardSize);

	if (!deck || oldCard.symb == 0) return false;

	deck.seekp(cardSize * index, std::ios::beg);
	deck.write(reinterpret_cast<const char*>(&card), cardSize);

	if (!deck) return false;

	printCard(oldCard);
	deck.close();
	return true;
}

bool removeCardFromBF(const char* fileName, std::size_t deckIndex) {
	if (deckIndex > cardsCount || deckIndex < 0) return false;

	std::ifstream deck(fileName, std::ios::binary);
	if (!deck.is_open()) {
		std::cerr << "Cannot open file for reading!";
		return false;
	}

	std::ofstream temp("temp.bin", std::ios::binary);
	if (!temp.is_open()) {
		std::cerr << "Cannot open file for writing!";
		return false;
	}

	int index = 0;
	Card card = {};
	while (deck){
		if (index != deckIndex) {
			deck.seekg(index * sizeof(card), std::ios::beg);
			deck.read(reinterpret_cast<char*>(&card), sizeof(card));
			if (card.symb == 0) { index++; continue; }

			temp.seekp(index * sizeof(card), std::ios::beg);
			temp.write(reinterpret_cast<const char*>(&card), sizeof(card));
		}
		index++;
	}

	deck.close();
	temp.close();

	remove(fileName);
	rename("temp.bin", fileName);
	
	return true;
}