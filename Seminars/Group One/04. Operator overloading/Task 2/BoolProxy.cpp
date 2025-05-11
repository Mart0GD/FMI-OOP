#include "BoolProxy.hpp"

BoolProxy::BoolProxy(int index, const BoolArray* owner)
	: index(index), owner(owner) { }


BoolProxy::BoolProxy(const BoolProxy& other)
	: index(other.index), owner(other.owner) { }
BoolProxy& BoolProxy::operator=(const BoolProxy& other) {
	if (*this == other) return *this;

	index = other.index;
	owner = other.owner;

	return*this;
}

BoolProxy& BoolProxy::operator=(int32_t element) {
	if (element != 1 && element != 0) throw std::invalid_argument("Not a binary element!");

	owner->data[index / 8] |= (element << (index % 8));

	return*this;
}

BoolProxy::operator bool() const {
	return (*owner)[index];
}