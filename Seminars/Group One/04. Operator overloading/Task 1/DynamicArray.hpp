#pragma once
#include <iostream>

class DynamicArray {

	friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr);
	friend std::istream& operator>>(std::istream& os, DynamicArray& arr);

public:
	DynamicArray(int32_t size = 32);

	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& other);

	DynamicArray(DynamicArray&& other) noexcept;
	DynamicArray& operator=(DynamicArray&& other) noexcept;

	~DynamicArray() noexcept;

	int32_t* data() const { return _data; }
	int32_t position() const { return _position; }
	int32_t size() const { return _size; }

	DynamicArray operator+(int32_t element);
	DynamicArray& operator+=(int32_t element);

	DynamicArray operator+(const DynamicArray& other);
	DynamicArray& operator+=(const DynamicArray& other);

	DynamicArray operator-(int32_t element);
	DynamicArray& operator-=(int32_t element);

	DynamicArray& operator=(const int32_t* arr);

	int32_t operator[](int32_t index) const;
	int32_t& operator[](int32_t index);

	int32_t operator()(int32_t element) const;


	class Iterator {

		friend class DynamicArray;

	public:

		Iterator& operator ++ ();
		Iterator operator ++ (int);

		bool operator == (const Iterator& other) const;
		bool operator != (const Iterator& other) const;

		int operator * () const;
		int& operator * ();

	private:
		Iterator(int* pos) : position(pos) {}

	private:
		int* position;
	};

	Iterator begin() { return Iterator(_data); }
	Iterator end() { return Iterator(_data + _position); }

private:
	bool resize(uint32_t amount);

private:
	int32_t* _data;
	uint32_t _position;

	int32_t _size;
};

bool operator < (const DynamicArray& da1, const DynamicArray& da2);
bool operator <= (const DynamicArray& da1, const DynamicArray& da2);

bool operator > (const DynamicArray& da1, const DynamicArray& da2);
bool operator >= (const DynamicArray& da1, const DynamicArray& da2);

bool operator == (const DynamicArray& da1, const DynamicArray& da2);
bool operator != (const DynamicArray& da1, const DynamicArray& da2);



