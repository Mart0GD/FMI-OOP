#pragma once

/*
����� ����� ��� ������ ��������������:
- ��� �� ��������������: �������� ��� � ���������� �������, ����� �� �������� ���������.
- ��� �� ������: �������� ��� � ���������� �������, ����� �� �������� ���������.
- ����� � ���������: ����� � ������� �������.
- ISBN: ������� ����, �������� 13 �����, ����������� �� � ������� ������: 978-d-dd-dddddd-d. ��� ������ ������� � 978. �� ������� �� ��������� ��������� �����.
*/

#include "ISBN.hpp"

class Book {

public:
	Book(const char* title, const char* author, float weight, const ISBN& isbn);

	Book(const Book& other);
	Book& operator=(const Book& other);

	Book(Book&& other) noexcept;
	Book& operator=(Book&& other) noexcept;

	~Book() noexcept;
		
	float getWeight() const { return weight; }
	const ISBN& getIsbn() const { return isbn; }

	static bool serialize(const Book& book, std::ostream& os);
	static Book deserialize(std::istream& is);

private:
	char* title;
	char* author;
	float weight;

	const ISBN isbn;
};