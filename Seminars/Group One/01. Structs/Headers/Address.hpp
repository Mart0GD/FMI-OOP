#pragma once
#ifndef ADDRESS_H
#define ADDRESS_H
#define MAX_TOWN_LEN 32
#define MAX_STREET_LEN 64
/*
Задача 4.
Да се реализира структура, която представя адрес. Той се състои от град (символен низ с не повече от 32 символа); пощенски код (цяло число без знак); улица (символен низ с не повече от 64 символа); номер (цяло число без знак); една буква (към номера); вход, етаж, апартамент (малки цели числа без знак). Примерен адрес би бил: "София", 1234, "ул. Цар Симеон", 10 а, вх. 2, ет. 7, ап. 30.
Да се напишат методи, позволяващи въвеждане и извеждане на адрес от стандартния вход / изход.

*/

struct Address {
	char town[MAX_TOWN_LEN] = {};
	unsigned postalCode;
	char street[MAX_STREET_LEN] = {};
	unsigned streetNumber;
	char streetLetter;
	unsigned short entrance;
	unsigned short floor;
	unsigned short apt;
}; 

void ReadAddress(Address& address);
void RandomAddress(Address& address);
void PrintAddress(const Address& address);

#endif