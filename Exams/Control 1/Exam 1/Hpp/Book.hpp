#pragma once

/*
Всяка книга има четири характеристики:
- Име на произведението: символен низ с произволна дължина, който ще заделите динамично.
- Име на автора: символен низ с произволна дължина, който ще заделите динамично.
- Тегло в килограми: число с плаваща запетая.
- ISBN: Отделен клас, съдържащ 13 цифри, представящи се в следния формат: 978-d-dd-dddddd-d. Той винаги започва с 978. За цифрите не заделяйте динамична памет.
*/

#include "ISBN.hpp"

class Book {

public:
	Book(const char* title, const char* author, float weight, const ISBN& isbn);

	Book(const Book& other);
	Book& operator=(const Book& other);

	Book(Book&& other) noexcept;
	Book& operator=(Book&& other) noexcept;

	~Book() noexcept;
		
	float getWeight() const { return weight; }
	const ISBN& getIsbn() const { return isbn; }

	static bool serialize(const Book& book, std::ostream& os);
	static Book deserialize(std::istream& is);

private:
	char* title;
	char* author;
	float weight;

	const ISBN isbn;
};