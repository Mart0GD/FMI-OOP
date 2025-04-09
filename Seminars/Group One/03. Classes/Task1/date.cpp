#include <exception>
#include <iostream>
#include <fstream>
#include "date.hpp"


constexpr char days[7][10] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };

Date::Date(uint32_t day, uint32_t month, uint32_t year) {
	if (!setDay(day) ||
		!setMonth(month) ||
		!setYear(year)) {
		throw std::invalid_argument("Invalid params");
	}
}
Date::Date(std::istream& is = std::cin, char separator) {
	if(!is) throw std::invalid_argument("file not opened!");

	if (!readFromFile(is, separator)) {
		throw std::invalid_argument("Invalid params");
	}
}

bool Date::readFromFile(std::istream& is, char separator) {
	uint16_t year, month, day;
	char chr;

	is >> day >> chr;
	if (!is || chr != separator) return false;
	is >> month >> chr;
	if (!is || chr != separator) return false;
	is >> year;
	if(!is || !isValidDate(year, month, day)) return false;

	this->year = year;
	this->month = month;
	this->day = day;

	return true;
}

bool Date::setDay(uint32_t day) {
	if (!isValidDay(this->year, this->month, day)) return false;
	this->day = day;
}
bool Date::setMonth(uint32_t month) {
	if (!isValidMonth(this->year, month)) return false;
	this->month = month;
}
bool Date::setYear(uint32_t year) {
	if (!isValidYear(year)) return false;
	this->year = year;
}

bool Date::isValidDate(uint32_t year, uint32_t month, uint32_t day) {
	return
		isValidYear(year) &&
		isValidMonth(year, month) &&
		isValidDay(year, month, day);
}
bool  Date::isValidYear(uint32_t year) {
	return year >= 0 && year <= 2100;
}
bool  Date::isValidMonth(uint32_t year, uint32_t month) {
	return month >= 1 && month <= 12;
}
bool  Date::isValidDay(uint32_t year, uint32_t month, uint32_t day) {
	return day >= 1 && day <= daysInMonth(year, month);
}
uint32_t Date::daysInMonth(uint32_t year, uint32_t month) {
	bool isLeap = isLeapYear(year);
	uint32_t maxDays = 0;

	switch (month)
	{
		case 2: maxDays += isLeap ? 29 : 28;
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			maxDays += 30;
			break;

		default: maxDays += 31;
	}

	return maxDays;
}


void Date::print() const  {
	std::cout << this->day << '-' << this->month << '-' << this->year << std::endl;
}
bool Date::addDays(int days) {
	if (days <= 0) return false;

	this->day += days;
	while (day > daysInMonth(year, month)) {
		day -= daysInMonth(year, month);
		month++;
		if (month > 12) {
			month = 1;
			year++;
		}
	}

	return true;
}
int Date::compare(const Date& other) const {
	if (other.year == other.year) {
		if (this->month == other.month) return this->day - other.day;
		else return this->month - other.month;
	}
	else return this->year - other.year;
}
bool Date::changeDate(uint32_t day, uint32_t month, uint32_t year) {
	if (!setDay(day) ||
		!setMonth(month) ||
		!setYear(year)) {
		return false;
	}
}
bool Date::changeDate(const Date& date) {
	if (!setDay(date.day) ||
		!setMonth(date.month) ||
		!setYear(date.year)) {
		return false;
	}
}
bool Date::isLeapYear(uint32_t year)
{return  (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);}
char* Date::dayOfWeek() const {
	int h_day = this->day;
	int h_month = this->month;
	int h_year = this->year;

	if (h_month < 3) {
		h_month += 12;
		h_year -= 1;
	}

	int K = h_year % 100;
	int J = h_year / 100;

	int h = (h_day + (13 * (h_month + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
	return (char*)days[h];
}
int Date::diff(const Date& date) const {
	int diff = 0;

	const Date* further = this->compare(date) > 0 ? this : &date;
	const Date* closer = further == this ? &date : this;

	for (int i = closer->year; i <= further->year; i++)
		diff += isLeapYear(i) ? 366 : 365;

	if (further->month != closer->month)
	{
		for (int i = 1; i < closer->month; i++)
			diff -= daysInMonth(closer->year,i);

		for (int i = further->month + 1; i <= 12; i++)
			diff -= daysInMonth(further->year, i);
	}

	if (further->day != closer->day)
	{
		diff -= closer->day;
		diff -= daysInMonth(further->year, further->month) - further->day;
	}

	return closer == this ? diff : -diff;
}