#pragma once
#include "Book.hpp"
/*
name	динамичен низ	Име на човека
borrowedBooks	масив от указатели към книги (Book)	Заети книги (максимум 5)
Реализирайте нужните конструктори, деструктори, гетъри и сетъри. Освен тях един Reader трябва да има реализиран следните методи:

void borrowBook(Book*) -> Добавя книга към заетите си книги. Да се хвърли грешка, ако книгата вече е заета (трябва да се обработи коректно извън класа).
void returnBook(const char*) -> Премахва книга с определено заглавие от заетите си книги. Да се хвърли грешка, ако книгата не е от затетите (трябва да се обработи коректно извън класа).
print -> принтира информация за читателя.
По време на работата ви може да се наложи да реализирате допълнителни методи!
*/

class Reader {

public:
	Reader(const char* name);

	Reader(const Reader& reader) = delete;
	Reader& operator=(const Reader& reader) = delete;

	~Reader() noexcept;

	const char* getName() const { return name; }

	void borrowBook(Book*& book);
	void returnBook(const char* name);
	void print() const;

private:
	void clear();

private:
	char* name;
	Book** borrowedBooks;
	int32_t bbCount;

	static const int32_t maxBooks;
};