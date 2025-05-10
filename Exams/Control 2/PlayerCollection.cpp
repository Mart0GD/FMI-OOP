#include "PlayerCollection.hpp"

PlayerCollection::PlayerCollection() 
	: count(0), capacity(startBuffer) 
{
	collection = new Player * [capacity];
	for (int i = 0; i < capacity; ++i) collection[i] = nullptr;
}

PlayerCollection::PlayerCollection(const PlayerCollection& other) {
	capacity = other.capacity;
	count = other.count;

	collection = new Player * [capacity];
	for (int i = 0; i < capacity; i++){
		if (!other.collection[i]) collection[i] = nullptr;
		else {
			try { collection[i] = other.collection[i]->clone(); }
			catch (const std::exception& e) { clear(); throw; }
		}
		
	}
}
PlayerCollection& PlayerCollection::operator=(const PlayerCollection& other) {
	if (this == &other) return *this;

	clear();
	capacity = other.capacity;
	count = other.count;

	collection = new Player * [capacity];
	for (int i = 0; i < count; i++) {
		try { collection[i] = other.collection[i]->clone(); }
		catch (const std::exception& e) { clear(); throw; }
	}

	return *this;
}

PlayerCollection::PlayerCollection(PlayerCollection&& other) noexcept {
	collection = other.collection;
	capacity = other.capacity;
	count = other.count;

	other.collection = nullptr;
}
PlayerCollection& PlayerCollection::operator=(PlayerCollection&& other) noexcept {
	if (this == &other) return *this;

	std::swap(collection, other.collection);
	capacity = other.capacity;
	count = other.count;


	return *this;
}

PlayerCollection::~PlayerCollection() noexcept {
	clear();
}

bool PlayerCollection::addPlayer(const Player& player) {
	if (getPlayer(player.getName())) return false;
	if (count + 1 == capacity) resize();

	collection[count++] = player.clone();
}

Player* const PlayerCollection::getPlayer(int32_t index) const {
	if (index >= 0 && index < capacity) return collection[index];
	else return nullptr;
}
Player* const PlayerCollection::getPlayer(const char* name) const {
	for (int i = 0; i < capacity; i++)
		if (collection[i] && strcmp(name, collection[i]->getName()) == 0) return collection[i];

	return nullptr;
}

bool PlayerCollection::removePlayer(const char* name) {

	int index = -1;
	for (int i = 0; i < capacity; i++)
		if (collection[i] && strcmp(name, collection[i]->getName()) == 0) index = i;

	if (index == -1) return false;

	delete collection[index];
	for (int i = index; i < capacity - 1; i++)
	{
		collection[i] = collection[i + 1];
	}
	--count;

	return true;
}

void PlayerCollection::clear() {
	for (int i = 0; i < capacity; i++){
		delete collection[i];
	}
	delete[] collection;
}
bool PlayerCollection::resize() {
	Player** old = collection;

	collection = new(std::nothrow) Player * [capacity * 2];
	if (!collection) return false;

	for (int i = 0; i < capacity; i++)
		collection[i] = old[i];

	for (int i = 0; i < capacity; i++)
		old[i] = nullptr;

	delete[] old;
	return true;
	
}