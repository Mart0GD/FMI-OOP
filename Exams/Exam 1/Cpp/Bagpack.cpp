#include "Bagpack.hpp"

Bagpack::Bagpack(float capacity)		
	: capacity(capacity)
{ 
	books = new Book * [bookBuffer];
	currentWeight = 0;
	booksCount = 0;
}


Bagpack::Bagpack(const Bagpack& other) 
	:capacity(other.capacity)
{
	books = new Book *[other.booksCount];
	
	for (int i = 0; i < other.booksCount; i++){
		try
		{
			Book* b = new Book(*other.books[i]);
			bool res = add(b);
			if (!res) throw std::invalid_argument("invalid book"); // maybe won't reach we use a valid object but jtbs
		}
		catch (const std::exception&)
		{
			for (int ii = 0; ii < i; ii++){
				delete books[i];
			}
			delete[] books;
		}
	}

}
Bagpack& Bagpack::operator=(const Bagpack& other) {
	if (capacity > other.capacity) throw std::invalid_argument("invalid operation!");
	if (this == &other) return *this;

	Bagpack copy(other);
	*this = std::move(copy);
	return *this;
}

Bagpack::Bagpack(Bagpack&& other) noexcept 
	: capacity(other.capacity), currentWeight(other.currentWeight), booksCount(other.booksCount)
{
	books = other.books;
	other.books = nullptr;
}
Bagpack& Bagpack::operator=(Bagpack&& other) noexcept {
	if (this == &other) return *this;

	std::swap(books, other.books);
	currentWeight = other.currentWeight;
	booksCount = other.booksCount;

	return *this;
}

Bagpack::~Bagpack() noexcept {
	for (int i = 0; i < booksCount; i++){
		delete books[i];
	}
	delete[] books;
}

bool Bagpack::add(Book*& book) {
	if (book->getWeight() + currentWeight > capacity) return false;

	if (booksCount + 1 >= bookBuffer) resize();
	books[booksCount++] = book;	
	currentWeight += book->getWeight();
	book = nullptr;

	return true;
}
Book* Bagpack::remove(const ISBN& isbn) {
	int index = -1;

	for (int i = 0; i < booksCount; i++){
		if (!strcmp(books[i]->getIsbn().getNumbers(), isbn.getNumbers())){
			index = i;
			break;
		}
	}
	if (index < 0) return nullptr;;

	Book* removed = books[index];
	for (int i = index; i < booksCount - 1; i++){
		books[i] = books[i + 1];
	}
	books[booksCount - 1] = nullptr;
	booksCount--;
	
	return removed;
}

bool Bagpack::serialize(const Bagpack& bp, std::ostream& os) {
	if (!os) return false;

	os.write(reinterpret_cast<const char*>(&bp.capacity), sizeof(bp.capacity));
	os.write(reinterpret_cast<const char*>(&bp.currentWeight), sizeof(bp.currentWeight));
	os.write(reinterpret_cast<const char*>(&bp.booksCount), sizeof(bp.booksCount));
	if (!os) return false;

	for (int i = 0; i < bp.booksCount && os; i++){
		Book::serialize(*bp.books[i], os);
	}

	return os.good();
}
Bagpack Bagpack::deserialize(std::istream& is) {
	if (!is) throw std::invalid_argument("invalid file!");

	float capacity = 0;
	float currentWeight = 0;
	int booksCount = 0;

	is.read(reinterpret_cast<char*>(&capacity), sizeof(capacity));
	is.read(reinterpret_cast<char*>(&currentWeight), sizeof(currentWeight));
	is.read(reinterpret_cast<char*>(&booksCount), sizeof(booksCount));
	if (!is) throw std::invalid_argument("bad file!");

	Bagpack bp(capacity);
	for (int i = 0; i < booksCount && is; i++){
		try {
			Book* book = new Book(Book::deserialize(is)); // need a copy ctor
			bool res = bp.add(book);
			if (!res) throw "full capacity!";
		}
		catch (std::invalid_argument& e) {
			throw std::invalid_argument("bad file!");
		}
	}
	

	return bp;
}

bool Bagpack::resize() {
	Book** old = books;

	books = new(std::nothrow) Book*[bookBuffer * 2];
	if (!books) {
		books = old;
		return false;
	}

	for (int i = 0; i < booksCount; i++){
		books[i] = old[i];
	}

	delete[] old;
	bookBuffer *= 2;
	return true;
}