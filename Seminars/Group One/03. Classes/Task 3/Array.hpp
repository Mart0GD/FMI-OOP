#ifndef ARRAY_HPP
#define ARRAY_HPP

#include<iostream>
#include<functional>

/*
Реализирайте клас Array, който представлява динамичен масив от цели числа. За него трябва да можете:

да прочетете и изведете елементите му на екрана;
да прочетете и промените елемент на дадена (с индекс) позиция;
да добавите елемент в края на масива. Ако няма място - да се разшири;
да сравните два масива за равенство;
да го сортирате в нарастващ ред;
да го филтрирате (премахвате някои елементи - остават всички, отговарящи на подадено свойство - предикат);
обърнете Помислете как можете да оптимизирате някои от операциите - например сортирането да не прави нищо ако знаете, че вече е сортиран.
*/

class Array {

public:
	Array(uint32_t capacity);

	Array(const Array& other);
	Array& operator=(const Array& other);

	Array(Array&& other) noexcept;
	Array& operator=(Array&& other) noexcept;

	void append(int32_t element);
	bool setAtIndex(int32_t element, uint32_t index);

	uint32_t getSize() { return size; }
	int32_t getAtIndex(uint32_t index) const { return data[index]; }

	void print(std::ostream& os = std::cout ) const;
	int equals(const Array&);
	void sort();
	void filter(bool(*func)(int32_t));

	~Array();

private:
	void expand();

private:
	int32_t* data;
	uint32_t size;
	uint32_t capacity;

	bool sorted;
};

#endif