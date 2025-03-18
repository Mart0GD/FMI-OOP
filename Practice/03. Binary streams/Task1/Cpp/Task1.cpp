#include <iostream>
#include <fstream>

#include "Person.hpp"
#pragma warning(disable: 4996)
/*


Ќапишете програма, ко€то работи в 2 различни режима в зависимост от бро€ на аргументите на командни€ ред:

Read режим
јко има само 1 команден аргумент, който е низ репрезентиращ името на бинарен файл. ѕрограмата тр€бва да прочете информаци€ за обект от тип Person и да принтира този обект на конзолата.

Write режим
јко има повече от аргументите на командни€ ред са повече от 1 и са следните (в следни€т ред):

низ, който репрезентира име на файл,
низ, който репрезентира име на човек,
низ, който репрезентира фамили€ на човек,
ц€ло число, което репрезентира години на човек,
реално число, което репрезентира тежест в килограми на човек.
ƒобавете валидаци€ за коректност на реда на аргументите и техните типове. «аписвате данните в структура тип Person и после записвате тази структура в подадени€т файл.


*/

int main1(int argc, char* args[]) {

	char* fileName = new(std::nothrow) char[strlen(args[0])];
	if (!fileName) return -1;

	strcpy(fileName, args[1]);
	std::fstream file(fileName, std::ios::out | std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Cannot open file for read!";
		return -1;
	}

	Person p = {};
	if (argc - 1 == 1)
	{
		bool res = read(p, fileName);
		if (!res) return -1;
		printPerson(p);
	}
	else {
		createPerson(p, argc, args);
		write(p, fileName);
	}

	free(p);
}