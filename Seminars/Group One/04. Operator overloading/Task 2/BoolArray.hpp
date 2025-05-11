#pragma once
#include <iostream>
#include "BoolProxy.hpp"
#include "Iterator.hpp"

constexpr int32_t INITIAL_CAP{ 4 };

class BoolProxy;
class Iterator;

class BoolArray {

	friend class BoolProxy;
	friend class Iterator;

public:

	friend std::ostream& operator << (std::ostream& os, const BoolArray& arr);
	friend std::istream& operator >> (std::istream& is, BoolArray& arr);

public:
	BoolArray();

	BoolArray(const BoolArray& other);
	BoolArray& operator=(const BoolArray& other);

	BoolArray& operator=(uint32_t element);

	~BoolArray();

	int32_t count() const { return _count; }

	Iterator begin() { return Iterator(data, 0); }
	Iterator end() { return Iterator(data, _count); }

public:

	BoolArray& operator+=(bool element);
	BoolArray& operator+=(const BoolArray& other);

	bool operator[](int32_t index) const;
	BoolProxy operator[](int32_t index);

	operator uint32_t();

private:
	void clear();
	bool resize();

private:
	uint8_t* data;
	int32_t _count, cap;
};

BoolArray operator+(const BoolArray& arr, bool element);
BoolArray operator+(const BoolArray& arr1, const BoolArray& arr2);

bool operator<(const BoolArray& arr1, const BoolArray& arr2);
bool operator<=(const BoolArray& arr1, const BoolArray& arr2);

bool operator>(const BoolArray& arr1, const BoolArray& arr2);
bool operator>=(const BoolArray& arr1, const BoolArray& arr2);

bool operator==(const BoolArray& arr1, const BoolArray& arr2);
bool operator!=(const BoolArray& arr1, const BoolArray& arr2);
