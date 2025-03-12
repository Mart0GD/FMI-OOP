#include <iostream>

struct Date {
	uint16_t year;
	uint8_t month;
	uint8_t day;
};

bool readDate(Date& date, std::istream& stream);
bool validate(uint16_t year, uint8_t month, uint8_t date);
int compareDates(const Date& d1, const Date& d2);
unsigned diff(const Date& date1, const Date& date2);

// year opps
int compareYears(const Date& d1, const Date& d2);
bool isLeapYear(uint16_t year);

// month opps
uint8_t daysInMonth(uint8_t month, uint16_t year);