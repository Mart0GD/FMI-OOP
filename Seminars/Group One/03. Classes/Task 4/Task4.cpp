#include "MarkdownTransformer.hpp"
#include <iostream>

int main4() {
	MarkdownTransformer mt;

	try
	{
		mt = MarkdownTransformer("random_text.txt");
	}
	catch (const std::exception& e)
	{
		std::cerr << "Constructor failed!";
		throw e;
	}

	try
	{
		mt.makeHeading(0);
		mt.makeBold(1, 0, mt.getRowSize(1));
		mt.makeBold(10, 0, mt.getRowSize(10));
		mt.makeItalic(3, 0, mt.getRowSize(3));
		mt.makeCombine(4, 0, mt.getRowSize(4));

		mt.addLine("Hello, there!");
		mt.remove(12);

		mt.exit();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	
	return 0;
}