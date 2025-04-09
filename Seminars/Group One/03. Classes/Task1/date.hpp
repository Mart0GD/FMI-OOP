#pragma once
#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>


class Date {
public:
	Date() = delete;
	Date(std::istream& is, char separator = '-');
	Date(uint32_t day, uint32_t month, uint32_t year);

	bool setDay(uint32_t day);
	bool setMonth(uint32_t month);
	bool setYear(uint32_t year);

	uint32_t getDay() const { return day; }
	uint32_t getMonth() const { return month; }
	uint32_t getYear() const { return year; }

	void print() const;
	int compare(const Date& other) const;
	char* dayOfWeek() const;
	int diff(const Date& date) const;
	bool addDays(int days);
	bool changeDate(uint32_t day, uint32_t month, uint32_t year);
	bool changeDate(const Date& date);
	bool readFromFile(std::istream& is, char separator);

private:
	static bool isValidDate(uint32_t year, uint32_t month, uint32_t day);
	static bool isValidYear(uint32_t year);
	static bool isValidMonth(uint32_t year, uint32_t month);
	static bool isValidDay(uint32_t year, uint32_t month, uint32_t day);
	static bool isLeapYear(uint32_t year);
	static uint32_t daysInMonth(uint32_t year, uint32_t month);

private:
	uint32_t day;
	uint32_t month;
	uint32_t year;

};

#endif