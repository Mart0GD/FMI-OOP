#include <iostream>
#include <iomanip>
#include <climits>
#include "Date.hpp"

int getDashCount(std::istream& stream, int index);

bool readDate(Date& date, std::istream& stream) {
	unsigned y, m, d;
	unsigned char ch;

	int dashCount = getDashCount(stream, stream.tellg());

	if (dashCount == 2){

		stream >> d >> ch;
		if (!stream || ch != '-') return false;
		stream >> m >> ch;
		if (!stream || ch != '-') return false;
		stream >> y;
		if (!stream) return false;

		if (!validate(y, m, d)) return false;
		date.year = y;
		date.month = m;
		date.day = d;

	}
	else
	{
		stream >> d >> ch;
		if (!stream || ch != '-') return false;
		stream >> y;
		if (!stream) return false;

		m = d % 100;
		d /= 100;
		if (!validate(y, m, d)) return false;

		date.year = y;
		date.month = m;
		date.day = d;
	}
}

bool validate(uint16_t year, uint8_t month, uint8_t date) {
	return
		year <= 2100 && year >= 1900 &&
		month >= 1 && month <= 12 &&
		date >= 1 && date <= 31;
}

unsigned diff(const Date& date1, const Date& date2) {
	unsigned diff = 0;
	const Date& end = compareDates(date1, date2) > 0 ? date1 : date2;
	const Date& start = (&end == &date1) ? date2 : date1;
	
	for (int i = start.year + 1; i < end.year; i++){
		if (isLeapYear(i)) diff += 366;
		else diff += 365;
	}

	if (start.year == end.year){
		for (int i = start.month; i < end.month; i++){
			diff += daysInMonth(i, start.year);
		}
	}
	else
	{
		for (int i = start.month; i <= 12; i++)
			diff += daysInMonth(i, start.year);

		for (int i = 1; i < end.month; i++)
			diff += daysInMonth(i, end.year);
	}

	diff -= start.day;
	diff += end.day;

	return diff;

}

int compareYears(const Date& d1, const Date& d2) {
	return d1.year - d2.year;
}

int compareDates(const Date& d1, const Date& d2) {
	int yearDiff = (d1.year - d2.year);
	int monthDiff = (d1.month - d2.month);
	int dayDiff = (d1.day - d2.day);

	if (yearDiff == 0 && monthDiff == 0 && dayDiff == 0) return 0;
	int res = yearDiff > 0 
		|| yearDiff == 0 && monthDiff > 0 
		|| yearDiff == 0 && monthDiff == 0 && dayDiff > 0 ? 1 : -1;

	return res;
}

uint8_t daysInMonth(uint8_t month, uint16_t year){
	uint8_t days = 0;
	switch (month)
	{
		case 4:
		case 6:
		case 9:
		case 11: days -= 1;
		default: 
			days += 31;
		break;
		case 2: days += isLeapYear(year) ? 29 : 28;
	}

	return days;
}

bool isLeapYear(uint16_t year) {
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int getDashCount(std::istream& stream, int index) {
	int dashes = 0;
	char ch = ' ';
	stream >> ch;
	do
	{
		stream.get(ch);
		if (ch == '-') dashes++;
	} while (stream && ch != ' ' && ch != '\n');
	stream.clear();
	stream.seekg(index, std::ios::beg);

	return dashes;
}

