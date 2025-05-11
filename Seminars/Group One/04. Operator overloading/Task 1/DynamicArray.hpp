#pragma once
#include <iostream>

constexpr int32_t INITIAL_CAP = 32;

class DynamicArray {

public:

	friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr);
	friend std::istream& operator>>(std::istream& is, DynamicArray& arr);

public:
	DynamicArray();

	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& other);

	~DynamicArray();

	int32_t count() const { return _count; }

public:

	DynamicArray& operator+=(int32_t element);
	DynamicArray& operator+=(const DynamicArray& arr);
	DynamicArray& operator-=(int32_t element);

	int32_t operator[](int32_t index) const; 
	int32_t& operator[](int32_t index);
	int32_t operator()(int32_t index);

private:
	void clear();
	bool resize();

private:
	int32_t* data;
	int32_t _count, cap;
};

bool operator<(const DynamicArray& a1, const DynamicArray& a2);
bool operator<=(const DynamicArray& a1, const DynamicArray& a2);

bool operator>(const DynamicArray& a1, const DynamicArray& a2);
bool operator>=(const DynamicArray& a1, const DynamicArray& a2);

bool operator==(const DynamicArray& a1, const DynamicArray& a2);
bool operator!=(const DynamicArray& a1, const DynamicArray& a2);

DynamicArray operator+(const DynamicArray& arr, int32_t element);
DynamicArray operator+(const DynamicArray& arr1, const DynamicArray& arr2);
DynamicArray operator-(const DynamicArray& arr, int32_t element);