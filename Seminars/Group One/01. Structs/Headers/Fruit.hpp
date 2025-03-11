#pragma once
/*
Задача 3. Структурата Fruit, определяща плод, е дефинирана по следния начин:
struct Fruit
{
  char name[32]; // име на плод
  color cl;      // цвят на плод
  yn annual;     // едногодишен плод
  yn perennial;  // многогодишен плод
  yn tropical;   // тропически плод
};
където:
- color е изброен тип за цвят (напр. brown, green, orange, red, yellow и т.н.)
- yn е изброен тип с две стойности Yes и No
Напишете програма, която:
а) създава едномерен масив от указатели към структури, задаващи плодове и прочита данните от клавиатурата;
б) сортира по име, цвят и продължителност на плододаване плодовете, зададени чрез масива;
в) извежда данните за плодовете, зададени чрез масива, след сортирането им;
г) извежда многогодишните, тропически плодове с даден цвят, сортирани в низходящ ред по име на плода.
За целта да се дефинират подходящи функции. Постарайте се да гарантирате коректност на данните.
*/
#include "Enums.hpp"
#define NAME_LEN 32

struct Fruit {
	char name[NAME_LEN];
	Color color;
	YN annual;
	YN perennial;
	YN tropical;
};

Fruit CreateFruit();
int getWeight(const Fruit& fruit);
void SortFruits(Fruit* fruitsm, size_t count);
void PrintTropicalPerennialFruit(Fruit* fruits, size_t count, const Color color);
void PrintFruit(const Fruit& fruit);
const char* getColor(Color color);