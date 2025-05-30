﻿#include <iostream>
#include <fstream>

#include "Car.hpp"
#include "CarRegister.hpp"
#include "date.hpp"

/*
Реализирайте класове, представящи Човек (Person) и Кола (Car).

Човекът трябва да има три имена (символни низове с произволна дължина), дата на раждане (обект Date) и пол (изброен тип). Нека датата на раждане и полът се задават при конструиране и не могат повече да се променят (данните са const). Имената трябва да могат да се променят свободно, но да не са празни. Подсигурете подходящи конструктори, деструктор и методи за достъп. Реализирайте метод за извеждане на данните на екрана.

Колата има модел и марка, които са символни низове с произволна дължина, дата на производство (Date), цвят (unsigned int) и собственик (Person). Модела, марката и датата на производство не могат да се променят (направете ги const), цветът винаги е зададен и трябва да е в RGB формат (най-младшия байт на числото е стойност за синьо, вторият - за зелено, третият за червено; най-старшият байт трябва да е винаги 0), а собственика е указател към Person, който може да е зададен, но може и да не е (nullptr), когато няма такъв. За колата реализирайте подходящи конструктори и методи за достъп, също извеждане на екрана и смяна на собственик.

Реализирайте система (като клас), която поддържа множество коли и множество хора. Трябва да можете да генерирате различни справки, като:

колко хора са собственици на повече от една кола
колко коли нямат собственици
кои коли са собственост на даден човек
кои хора имат определен брой коли (0, 1, 2 и т.н.) Също да можете да прехвърлите кола към нов собственик (продажба). На този етап не се изисква добавяне или премахване на коли и хора в системата след създаването ѝ.
*/


/*
Questions:

1. --> "цветът винаги е зададен", означава ли че е константен и ако не е просто винаги да има default-на стойност като режем първия байт???

2. --> когато сме в деструкторите на колата махаме колата като собственост на човека и като сме в човека го махаме като собственик?

3 --> човека трябва да има указател към кола, нали не е указано, но е нужно за пълна функционалност?

4 --> exception handling-а - лошо ли е, че имам изключения в конструкторите, а не в сетърите?

5 --> да оставям ли датата като копие (лек обект е)? 

6 --> copy конструктора на Car -> правилно ли е да задържа собственика?

7 --> в car регистъра в отделните методи не хвърлям изключения, но в конструкторите и важните методи го правя, това гршка в подхода ли е, защото се променя стила?
*/

int main2() {

	std::ifstream cars("Register.txt");
	std::ifstream people("People.txt");
	if (!cars.is_open() || !people.is_open()) {
		std::cerr << "Cannot open file for reading!";
		return 0;
	}

	CarRegister reg = CarRegister();
	
	Person p1(people);
	Person p2(people);

	Car car1(cars, p1);
	Car car2(cars, p2);
	Car car3(cars, p1);


	reg.insertCar(car1);
	reg.insertCar(car2);
	reg.insertCar(car3);

	//int count = reg.multipleCarOwnersCount();
}