#include "ISBN.hpp"
#include "Book.hpp"
#include "Bagpack.hpp"

#include <fstream>

int main() {

	try
	{
		ISBN isbn1("987-1-22-176129-1");
		ISBN isbn2("987-3-12-879352-2");

		Book* book1 = new Book("Harry Potter", "J.K Rolling", 3.4, isbn1);
		Book* book2 = new Book("Someting Potter", "Pesho", 3.4, isbn2);

		Bagpack bp(10);

		bp.add(book1);
		bp.add(book2);

		std::fstream file("Test.bin", std::ios::binary | std::ios::in | std::ios::out);
		if (!file) throw "bad file!";

		Bagpack::serialize(bp, file);
		file.close();
		file.open("Test.bin", std::ios::binary | std::ios::in | std::ios::out);

		Bagpack bp2 = Bagpack::deserialize(file);
		Bagpack bp3(11);

		Book* b3 = new Book("Smt", "Smt", 10, isbn1);
		bp3.add(b3);
		bp2 = bp3;
		int a = 0;
	}
	catch (const std::exception&)
	{

	}

	return 0;
}