#include "Array.hpp"
#include <iostream>
#include <utility>


// ctor/dtor
Array::Array(uint32_t capacity) {
	data = new int32_t[capacity];
	this->capacity = capacity;
	this->size = 0;
	sorted = false;
}

// copy
Array::Array(const Array& other) : size(other.size), capacity(other.capacity), sorted(false)
{
	data = new int32_t[capacity];
	for (int i = 0; i < capacity; i++)
		data[i] = other.data[i];
}
Array& Array::operator=(const Array& other){
	if (this == &other) return *this;

	Array copy(other);
	*this = std::move(copy);
	return *this;
}

// move
Array::Array(Array&& other) noexcept : 
	size(other.size), capacity(other.capacity)
{
	this->data = other.data;
	other.data = nullptr;
}
Array& Array::operator=(Array&& other) noexcept {
	size = other.size;
	capacity = other.capacity;

	std::swap(this->data, other.data);
	return *this;
}

Array::~Array() noexcept  {
	delete[] data; 
	data = nullptr;
}

// public 
bool Array::setAtIndex(int32_t element, uint32_t index){
	if (index >= capacity) return false;
	data[index] = element;
	sorted = false;
	return true;
}
void Array::append(int32_t element){
	if (size == capacity) expand();
	data[size++] = element;
	sorted = false;
}

void Array::sort() {
	if (sorted) return;

	int32_t temp = 0;
	bool swaped;
	for (size_t i = 0; i < this->capacity; i++){
		swaped = false;
		for (int j = 0; j < this-> capacity - 1 - i; j++){
			if (data[j] < data[j + 1]) continue;

			temp = data[j];
			data[j] = data[j + 1];
			data[j + 1] = temp;
			swaped = true;
		}
		if (!swaped) break;
	}
}
void Array::filter(bool(*func)(int32_t)) {
	int32_t* filtered = new(std::nothrow) int32_t[capacity];
	if (!filtered) return;
	int newSize = 0;

	for (int i = 0; i < this->size; i++)
		if (func(data[i])) filtered[newSize++] = data[i];

	delete[] data;

	data = filtered;
	this->size = newSize;

}
void Array::print(std::ostream& os) const {
	for (int i = 0; i < size; i++)
		os << data[i] << ' ';
}
int  Array::equals(const Array& other) {
	for (size_t i = 0; i < this->capacity && i < other.capacity; i++){
		if (this->data[i] != other.data[i]) return this->data[i] - other.data[i];
	}

	return this->capacity - other.capacity;
}

// private
void Array::expand() {
	int32_t* t = new int32_t[capacity * 2];

	for (int i = 0; i < capacity; i++){
		t[i] = data[i];
	}

	capacity *= 2;
	delete[] data;
	data = t;
}