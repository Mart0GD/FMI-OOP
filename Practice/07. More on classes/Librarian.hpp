#pragma once
#include "Book.hpp"
#include "Library.hpp"
#include "Reader.hpp"
/*
Един библиотекар ще трябва да може да извършва различни операции като:

да заема книга на читател.
да приема обратно книга от читател.
да принтира информация за книга, книги и читатели.
да проверява заетост на книга.
*/

class Librarian {

public:

	Librarian(Library& librray);

	bool handBook(const char* title, const char* readerName);
	bool acceptBook(const char* title, const char* readerName);

	void printBook(const Book* book);
	void printBooks(const Book** books, int cnt);
	void printReaders(const Reader** readers, int cnt);

	bool checkBorrowState(const Book* book);
	bool checkBorrowState(const char* title);

private:
	Library* lib;
};