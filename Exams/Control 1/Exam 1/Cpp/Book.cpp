#include "Book.hpp"
#pragma warning(disable: 4996)

Book::Book(const char* title, const char* author, float weight, const ISBN& isbn) 
	: isbn(isbn), weight(weight)
{
	this->title = strcpy(new char[strlen(title) + 1], title);

	this->author = new(std::nothrow) char[strlen(author) + 1];
	if (author) strcpy(this->author, author);
	else{
		delete[] title;
		throw std::bad_alloc();
	}
}

Book::Book(const Book& other) 
	:isbn(other.isbn), weight(other.weight)
{
	title = strcpy(new char[strlen(other.title) + 1], other.title);

	author = new(std::nothrow) char[strlen(other.author) + 1];
	if (author) strcpy(author, other.author);
	else {
		delete[] title;
		throw std::bad_alloc();
	}
}
Book& Book::operator=(const Book& other) {
	if (this != &other) return *this;

	Book copy(other);
	*this = std::move(copy);

	return *this;
}

Book::Book(Book&& other) noexcept
	:isbn(other.isbn), weight(other.weight)
{
	title = other.title;
	author = other.title;

	other.author = other.title = nullptr;
}
Book& Book::operator=(Book&& other) noexcept {
	if (this == &other) return *this;

	std::swap(title, other.title);
	std::swap(author, other.author);
	weight = other.weight;

	return *this;
}

Book::~Book() noexcept {
	delete[] title;
	delete[] author;
}

bool Book::serialize(const Book& book, std::ostream& os) {
	if (!os) return false;

	int titleLen = strlen(book.title) + 1;
	os.write(reinterpret_cast<const char*>(&titleLen), sizeof(titleLen));
	os.write(reinterpret_cast<const char*>(book.title), titleLen);
	if (!os) return false;

	int authorLen = strlen(book.author) + 1;
	os.write(reinterpret_cast<const char*>(&authorLen), sizeof(authorLen));
	os.write(reinterpret_cast<const char*>(book.author), authorLen);
	if (!os) return false;

	os.write(reinterpret_cast<const char*>(&book.weight), sizeof(book.weight));
	os.write(reinterpret_cast<const char*>(&book.isbn), sizeof(book.isbn));

	return os.good();
}
Book Book::deserialize(std::istream& is) {
	if (!is) throw std::invalid_argument("bad file!");

	//const char* title, const char* author, float weight, const ISBN& isbn

	int titleLen = 0;
	is.read(reinterpret_cast<char*>(&titleLen), sizeof(titleLen));

	char* titleBuffer = new(std::nothrow) char[titleLen];
	if (!titleBuffer) throw std::invalid_argument("bad file!");
	is.read(titleBuffer, titleLen);
	if(!is) throw "error reading!";
	

	int authorLen = 0;
	is.read(reinterpret_cast<char*>(&authorLen), sizeof(authorLen));

	char* authorBuffer = new(std::nothrow) char[authorLen];
	if (!authorBuffer) {
		delete[] titleBuffer;
		throw std::invalid_argument("bad file!");
	}
	is.read(authorBuffer, authorLen);
	if (!is) throw "error reading!";

	float weight;
	ISBN isbn;

	is.read(reinterpret_cast<char*>(&weight), sizeof(weight));
	is.read(reinterpret_cast<char*>(&isbn), sizeof(isbn));

	Book book(titleBuffer, authorBuffer, weight, isbn);

	return book;
}