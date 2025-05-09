#include "Librarian.hpp"

Librarian::Librarian(Library& lib) 
	:lib(&lib)
{ }

bool Librarian::handBook(const char* title, const char* readerName) {
	if (!title || !*title || !readerName || !*readerName) return false;

	Book* book = lib->findBook(title);
	Reader* reader = lib->findReader(readerName);
	if (!book || !reader) return false;

	try { reader->borrowBook(book); }
	catch (std::exception& e) { return false; }

	return true;
}
bool Librarian::acceptBook(const char* title, const char* readerName) {
	if (!title || !*title || !readerName || !*readerName) return false;

	Reader* reader = lib->findReader(readerName);
	try { reader->returnBook(title); }
	catch (std::exception& e) { return false; }

	return true;
}

void Librarian::printBook(const Book* book) { 
	if (!book) return;
	book->print(); 
}
void Librarian::printBooks(const Book** books, int cnt) {
	if (!books) return;

	for (int i = 0; i < cnt; i++)
		printBook(books[i]);
}
void Librarian::printReaders(const Reader** readers, int cnt) {
	if (!readers) return;

	for (int i = 0; i < cnt; i++)
		readers[i]->print();
}

bool Librarian::checkBorrowState(const Book* book) { return book->borrowed(); }
bool Librarian::checkBorrowState(const char* title) { return lib->findBook(title)->borrowed(); }