#include "Library.hpp"

Library::Library()
	:booksCount(0), readersCount(0), readersBuffer(64), booksBuffer(128)
{
	books = new Book * [booksBuffer];
	for (int i = 0; i < booksBuffer; ++i) books[i] = nullptr;

	readers = new(std::nothrow) Reader * [readersBuffer];
	if (!readers) {
		clear();
		throw std::bad_alloc();
	}
	for (int i = 0; i < readersBuffer; ++i) readers[i] = nullptr;
}

Library::Library(const Library& other) 
	:booksCount(0), readersCount(0), 
	 booksBuffer(other.booksBuffer), readersBuffer(other.readersBuffer)
{
	books = new Book*[other.booksBuffer];

	for (int i = 0; i < other.booksCount; ++i){
		try
		{
			addBook(other.books[i]->getTitle(), other.books[i]->getAuthor());
		}
		catch (const std::exception&)
		{
			clear(); throw;
		}
	}

	readers = new (std::nothrow) Reader * [other.readersBuffer];
	if (!readers) {
		clear();
		throw std::bad_alloc();
	}

	for (int i = 0; i < readersCount; i++){
		try
		{
			registerReader(other.readers[i]->getName());
		}
		catch (const std::exception&)
		{
			clear(); throw;
		}
	}

}
Library& Library::operator=(const Library& other) {
	if (this == &other) return *this;

	Library copy(other);
	*this = std::move(copy);

	return *this;
}

Library::Library(Library&& other) noexcept
	:booksBuffer(other.booksBuffer), readersBuffer(other.readersBuffer),
	 booksCount(other.booksCount), readersCount(other.readersCount)
{
	this->books = other.books;
	this->readers = other.readers;
	books = nullptr;
	readers = nullptr;

}
Library& Library::operator=(Library&& other) noexcept {
	if (this == &other) return *this;

	std::swap(books, other.books);
	std::swap(readers, other.readers);

	this->booksBuffer = other.booksBuffer;
	this->readersBuffer = other.readersBuffer;
	this->booksCount = other.booksCount;
	this->readersCount = other.readersCount;

	return *this;
}

Library::~Library() noexcept {
	clear();
}

void Library::addBook(const char* title, const char* author) {
	if (!title || !*title || !author || !*author) throw std::invalid_argument("bad input!");

	Book* hasDuplicate = findBook(title);
	if (hasDuplicate) throw std::invalid_argument("duplicate book!");
	if (booksCount + 1 >= booksBuffer) resizeBooks();

	books[booksCount++] = new Book(title, author);
}
void Library::registerReader(const char* name) {
	if (!name || !*name) throw std::invalid_argument("invalid input!");
	if (readersCount + 1 >= readersBuffer) resizeReaders();

	readers[readersCount++] = new Reader(name);
}

Book* Library::findBook(const char* title) {
	if (!title || !*title) return nullptr;

	for (int i = 0; i < booksCount; i++)
		if (strcmp(books[i]->getTitle(), title) == 0) return books[i];
	
	return nullptr;
}
Book** Library::findBooks(const char* author) {
	if (!author || !*author) return nullptr;

	Book** books = new(std::nothrow) Book * [booksCount];
	if (!books) return nullptr;

	Book* b = nullptr;
	int index = 0;
	int iter = 0;
	do
	{
		for (int i = index; i < booksCount; i++){
			if (strcmp(books[i]->getAuthor(), author) == 0) {
				b = books[i];
				index = i + 1;
				break;
			}
		}

		if (b){
			books[iter++] = b;
			b = nullptr;
		}
	} while (b);
	if (iter == 0) return nullptr;

	return books;
}
Reader* Library::findReader(const char* name) {
	if (!name || !*name) return nullptr;

	for (int i = 0; i < readersCount; i++) 
		if (strcmp(readers[i]->getName(), name) == 0) return readers[i];
	
	return nullptr;
}

bool Library::resizeBooks() {

	Book** old = books;
	books = new(std::nothrow) Book * [booksBuffer * 2];
	if (!books) {
		books = old;
		return false;
	}

	for (int i = 0; i < booksCount; i++)
	{
		books[i] = old[i];
		delete old[i];
	}
	delete[] old;
	booksBuffer *= 2;

	return true;
}
bool Library::resizeReaders() {
	Reader** old = readers;
	readers = new(std::nothrow) Reader * [readersBuffer * 2];
	if (!readers) {
		readers = old;
		return false;
	}

	for (int i = 0; i < readersCount; i++)
	{
		readers[i] = old[i];
		delete old[i];
	}
	delete[] old;
	readersBuffer *= 2;

	return true;
}

void Library::clear() {
	for (int i = 0; i < readersBuffer; i++) {
		delete readers[i]; readers[i] = nullptr;
	}
	delete[] readers;

	for (int i = 0; i < booksBuffer; i++){
		delete books[i]; books[i] = nullptr;
	}
	delete[] books;

}