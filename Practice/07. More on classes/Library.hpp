#pragma once
#include "Reader.hpp"
#include "Book.hpp"
/*
books	динамичен масив	Налични книги в библиотеката
readers	динамичен масив	Налични читатели
Реализирайте нужните конструктори, деструктори, гетъри и сетъри. Освен тях един Library трябва да има реализиран следните методи:

void addBook(const char*, const char*) -> Добавя книга в библитоеката. Не може да има 2 книги с еднакво заглавие.
void registerReader(const char*) -> Регистрира читател.
Book* findBook(const char*) -> Намира книга по заглавие.
Book** findBooks(const char*) -> Намира книги по име на автор
Reader* findReader(const char*) -> Намира читател по име на читател.
По време на работата ви може да се наложи да реализирате допълнителни методи!
*/

class Library {

public:
	Library();

	Library(const Library& other);
	Library& operator=(const Library& other);

	Library(Library&& other) noexcept;
	Library& operator=(Library&& other) noexcept;

	~Library() noexcept;

	void addBook(const char* title,const char* author);
	void registerReader(const char* name);

	Book* findBook(const char* title);
	Book** findBooks(const char* author);
	Reader* findReader(const char* name);

private:
	bool resizeBooks();
	bool resizeReaders();
	void clear();

private:
	Book** books;
	int32_t booksCount;

	Reader** readers;
	int32_t readersCount;


	int32_t booksBuffer;
	int32_t readersBuffer;
};