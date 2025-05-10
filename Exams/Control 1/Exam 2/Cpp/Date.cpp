#include "Date.hpp"

Date::Date() 
	:Date(1, 1, 1970)
{ }
Date::Date(uint32_t day, uint32_t month, uint32_t year) {
	if (!isValid(day, month, year)) throw std::invalid_argument("invalid day!");

	//magic here;
	date = day;
	date |= (((date >> 5) + month) << 5);
	date |= (((date >> 9) + (year - START_YEAR)) << 9);
}
Date::Date(const char* date) {
	if (!date || !*date) throw std::invalid_argument("invalid day!");

	char* str = nullptr;

	str = readString(date, '/');
	uint32_t day = parse(str);

	str = readString(date, '/');
	uint32_t month = parse(str);

	str = readString(date, '/');
	uint32_t year = parse(str);

	if (!isValid(day, month, year)) throw std::invalid_argument("invalid day!");

	this->date = day;
	this->date |= (((this->date >> 5) + month) << 5);
	this->date |= (((this->date >> 9) + (year - START_YEAR)) << 9);
}

Date::Date(const Date& other)
	:date(other.date)
{ }
Date& Date::operator=(const Date& other) {
	date = other.date;

	return *this;
}

bool Date::print(std::ostream& os)const  {
	if (!os) return false;

	os << getDay() << '/' << getMonth() << '/' << getYear();
	return os.good();
}
bool Date::isValid(uint32_t day, uint32_t month, uint32_t year) {
	if (year < 1970 || month > 12 || day > 31) return false;

	int isDayCorrect = false;
	int days = 0;
	switch (month)
	{
		case 2:
		days = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 29 : 28;
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			days = 30;
			break;

		default:
			days = 31;
			break;
	}

	return day <= days;
}
int Date::equals(const Date& other) const {
	if (getYear() == other.getYear())
	{
		if (getMonth() == other.getMonth()) return getDay() - other.getDay();
		return getMonth() - other.getMonth();
	}

	return getYear() - other.getYear();
}


uint32_t Date::parse(char* str) {
	int digits = strlen(str);

	uint32_t number = 0;
	while (*str){
		number *= 10;
		number += *str - '0';
		str++;
	}

	return number;
}
char* Date::readString(const char*& str, int delim) {
	if (!str || !*str) return nullptr;
	const int len = 10;

	static char buff[len + 1];
	int iter = 0;
	while (*str && *str != delim){
		buff[iter++] = *str;
		str++;
	}
	str++;
	buff[iter] = '\0';

	return buff;
}