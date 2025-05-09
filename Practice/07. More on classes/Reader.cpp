#include "Reader.hpp"
#pragma warning(disable:4996)

Reader::Reader(const char* name) 
	:bbCount(0)
{
	this->name = strcpy(new char[strlen(name) + 1], name);

	borrowedBooks = new(std::nothrow) Book * [maxBooks];
	if (!borrowedBooks) {
		delete[] this->name;
		throw std::bad_alloc();
	}
	for (int i = 0; i < maxBooks; ++i) borrowedBooks[i] = nullptr;
}
Reader::~Reader() noexcept {
	clear();
}

void Reader::borrowBook(Book*& book) {
	if (bbCount >= maxBooks) throw std::invalid_argument("exceding book limit!");
	else if (book->borrowed()) throw std::invalid_argument("book already borrowed!");

	borrowedBooks[bbCount++] = book;
	book->borrow();
}
void Reader::returnBook(const char* name){
	if (!name || !*name) throw std::invalid_argument("invalid input!");

	int index = -1;
	for (int i = 0; i < maxBooks; i++)
	{
		if (strcmp(borrowedBooks[i]->getTitle(), name) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) throw std::invalid_argument("no book matches this name!");

	borrowedBooks[index]->returnBook();
	borrowedBooks[index] = nullptr;
	for (int i = 0; i < maxBooks - 1; i++){
		borrowedBooks[i] = borrowedBooks[i + 1];
	}
}
void Reader::print() const {
	std::cout << name << " books: \n";
	for (int i = 0; i < maxBooks && borrowedBooks[i]; i++){
		borrowedBooks[i]->print();
	}
}
void Reader::clear() {
	for (int i = 0; i < maxBooks; i++){
		if (borrowedBooks[i]) borrowedBooks[i]->returnBook();
		borrowedBooks[i] = nullptr; 
	}
	delete[] borrowedBooks;
	delete[] name;
}


const int32_t Reader::maxBooks{ 5 };