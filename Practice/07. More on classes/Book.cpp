#include "Book.hpp"
#pragma warning(disable:4996)

Book::Book(const char* title, const char* author)
	:id(getNextId()), isBorrowed(false)
{
	if (!set(this->author, author) ||
		!set(this->title, title)) {
		clear();
		throw std::invalid_argument("invalid params!");
	}
}

Book::Book(const Book& other) 
	: Book(other.author, other.title)
{ isBorrowed = other.isBorrowed;}
Book& Book::operator=(const Book& other) {
	if (this == &other) return *this;

	author = strcpy(new char[strlen(other.author) + 1], author);

	title = new(std::nothrow) char[strlen(other.title) + 1];
	if (title) strcpy(title, other.title);
	if (!title) {
		delete[] author;
		throw std::bad_alloc();
	}
	
	isBorrowed = other.isBorrowed;
	return *this;
}

Book::~Book() {
	clear();
}

bool Book::borrow() {
	if (isBorrowed) return false;

	isBorrowed = true;
	return true;
}
void Book::returnBook() {
	if (!isBorrowed) throw std::invalid_argument("book isn't borrowed!");

	isBorrowed = false;
}
void Book::print() const {
	std::cout << title << ' ' << author << ' ' << isBorrowed << std::endl;
}


// private
bool Book::set(char*& where, const char* what) {
	if (!what || !*what) return false;

	char* temp = new(std::nothrow) char[strlen(what) + 1];
	if (!temp) return false;
	strcpy(temp, what);

	delete[] where;
	where = temp;
	return true;
}

void Book::clear() {
	if(title) delete[] title; title = nullptr;
	if(author) delete[] author; author = nullptr;
}

int32_t Book::nextId{ 0 };