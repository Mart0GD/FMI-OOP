#pragma once
#include <iostream>
/*
Клас BoolArray, който да реализира динамичен масив от bool (само стойности true/false). Всеки елемент трябва да заема един бит. За класа реализирайте следните оператори:

оператор за присвояване от uint32_t, който заменя масива с битовото представяне на аргумента си.
оператор за индексиране []. Трябва да позволява промяна на елемент;
оператори за сравнение (еквивалентност и наредба). Използвайте лексикографска наредба;
оператори + за добавяне на елемент в края на масива;
оператори + за конкатенация на два масива;
оператори за вход и изход в поток;
оператор за преобразуване към uint32_t, който връща число, съставено от битове, равни на първите 32 булеви стойности от масива. Ако са по-малко, числото да се допълни с 0 (false). За класа реализирайте итератор.
*/

class BoolProxy;

class BoolArray {

	friend std::ostream& operator<<(std::ostream& os, const BoolArray& arr);
	friend std::istream& operator>>(std::istream& is, BoolArray& arr);

public:

	class BoolProxy {

	public:

		BoolProxy(BoolArray& owner, int32_t pos);

		operator bool() const;

		BoolProxy& operator = (bool what);
		BoolProxy& operator = (const BoolProxy& other);

	private:
		int32_t pos;
		BoolArray& owner;
	};

	class Iterator {

		friend class BoolArray;

	public:
		Iterator operator++();
		Iterator& operator++(int);

		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;

		bool operator*() const;
		BoolArray::BoolProxy operator*();
	private:
		Iterator(BoolArray& owner, int32_t index) : owner{ owner }, index{ index } {};

	private:
		BoolArray& owner;
		int32_t index;
	};

	Iterator begin();
	Iterator end();

public:

	BoolArray(uint32_t cap = 4);

	BoolArray(const BoolArray& other);
	BoolArray& operator=(const BoolArray& other);

	BoolArray(BoolArray&& other) noexcept;
	BoolArray& operator=(BoolArray&& other) noexcept;

	~BoolArray() noexcept;

	uint8_t* data() const { return _data; }
	uint32_t allocated() const { return _allocated; }
	uint32_t size() const { return _size; }

	bool getBit(int position) const;
	void setBit(int position, bool value);

	BoolArray operator+(int32_t element);
	BoolArray& operator+=(int32_t element);

	BoolArray operator+(const BoolArray& other);
	BoolArray& operator+=(const BoolArray& other);

	bool operator [] (int32_t index) const;
	BoolProxy operator [] (int32_t index);

	operator uint32_t() const;

private:
	uint8_t* _data;

	uint32_t _allocated;
	uint32_t _size;
};

bool operator < (const BoolArray& arr1, const BoolArray& arr2);
bool operator <= (const BoolArray& arr1, const BoolArray& arr2);

bool operator > (const BoolArray& arr1, const BoolArray& arr2);
bool operator >= (const BoolArray& arr1, const BoolArray& arr2);

bool operator == (const BoolArray& arr1, const BoolArray& arr2);
bool operator != (const BoolArray& arr1, const BoolArray& arr2);