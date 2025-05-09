#pragma once 
#include <iostream>
/*
title	динамичен низ	Заглавие на книгата
author	динамичен низ	Име на автора на книгата
id	цяло число	Уникален номер за всяка книга
isBorrowed	булева	Дали книгата е взета
remainingTime	цяло число	Оставащо време (намалява при изпълнение)
Реализирайте нужните конструктори, деструктори, гетъри и сетъри. Освен тях един Book трябва да има реализиран следните методи:

bool borrow() -> Заема книгата
void returnBook() -> Връща книгата
print -> принтира информация за книгата
*/

class Book {

public:
	Book(const char* author, const char* title);

	Book(const Book& book);
	Book& operator=(const Book& book);

	~Book() noexcept;

	const char* getTitle() const { return title; }
	char* getAuthor() const { return author; }
	bool borrowed() const { return isBorrowed; }

	bool borrow();
	void returnBook();
	void print() const;

private:
	static bool set(char*& where, const char* what);
	static int32_t getNextId() { return nextId++; }
	void clear();

private:
	char* title;
	char* author;
	bool isBorrowed;
	//int32_t remainingTime; no functionallity described

	const int32_t id;
	static int32_t nextId;
};