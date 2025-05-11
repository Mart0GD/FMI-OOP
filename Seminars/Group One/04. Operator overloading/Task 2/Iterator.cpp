#include "Iterator.hpp"

Iterator::Iterator(uint8_t* data, int32_t index) 
	: data(data), index(index) { }

Iterator& Iterator::operator++ () {
	++index;
	return *this;
}
Iterator Iterator::operator ++ (int) {
	Iterator copy(*this);
	++(*this);

	return copy;
}

bool Iterator::operator * () const {
	return data[index / 8] & (1 << index % 8);
}
uint8_t* Iterator::operator -> () const {
	return data;
}

bool operator == (const Iterator& i1, const Iterator& i2) {
	return i1.getIndex() == i2.getIndex();
}
bool operator != (const Iterator& i1, const Iterator& i2) {
	return !(i1 == i2);
}