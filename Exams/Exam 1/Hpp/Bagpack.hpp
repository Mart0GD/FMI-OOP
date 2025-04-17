#pragma once

/*
Излизайки навън, искате да носите повечко книги в раницата си, но пък тя има ограничен капацитет спрямо теглото. Напишете и клас, който да представя раница, в която можете да имате произволно количество книги. Трябва да имате методи за добавяне и премахване на книга от раницата, като добавянето е възможно само ако раницата може да понесе теглото на добавената книга (заедно с теглото на всички книги, които вече са в нея). Какво тегло може да понесе една раница се задава при създаването ѝ. Този параметър повече не трябва да може да се променя. При премахване оказвате ISBN-а на книгата, която искате да извадите от раницата.

Изисква се да реализирате метод, който по подадена раница записва в двоичен файл цялата информация за нея. Трябва да предоставите възможност също и за възстановяване на данните за раница от такъв двоичен файл. Какво и как записвате във файла е ваш избор.

Допълнително налагаме ограничението обект, представящ ISBN, да може да се създава само при подаване на коректни стойности за всички негови цифри.

/*/
#include "Book.hpp"
#include "ISBN.hpp"

class Bagpack {
public:
	Bagpack(float capacity);

	Bagpack(const Bagpack& other);
	Bagpack& operator=(const Bagpack& other);

	Bagpack(Bagpack&& other) noexcept;
	Bagpack& operator=(Bagpack&& other) noexcept;

	~Bagpack() noexcept;

	float getCapacity() const { return capacity; }

	bool add(Book*& book);
	Book* remove(const ISBN& isbn);

	static bool serialize(const Bagpack& bp, std::ostream& os);
	static Bagpack deserialize(std::istream& is);

private:
	bool resize();

private:
	const float capacity;
	float currentWeight;

	Book** books;
	int booksCount;

	int bookBuffer = 12;
};