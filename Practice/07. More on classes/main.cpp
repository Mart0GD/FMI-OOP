#include "Book.hpp"
#include "Library.hpp"
#include "Librarian.hpp"
#include "Reader.hpp"

#include "crtdbg.h"

int main() {

	try
	{
		Library lib = Library();

		lib.addBook("The Shadow of the Wind", "Carlos Ruiz Zafón");
		lib.addBook("Circe", "Madeline Miller");
		lib.addBook("Never Let Me Go", "Kazuo Ishiguro");

		lib.registerReader("Georgi");
		lib.registerReader("Kudrit");

		Librarian grumpy = Librarian(lib);

		grumpy.handBook("The Shadow of the Wind", "Georgi");
		grumpy.handBook("The Shadow of the Wind", "Kudrit");

		Book* b = lib.findBook("The Shadow of the Wind");

		grumpy.acceptBook("The Shadow of the Wind", "Georgi");

		bool state = grumpy.checkBorrowState(b);
		grumpy.printBook(b);


	}
	catch (const std::exception& e)
	{

	}

	return 0;
}
