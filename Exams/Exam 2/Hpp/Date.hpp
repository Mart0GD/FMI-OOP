#pragma once

/*
Date - ����, ����� ��������� ������� ���� ���� 01.01.1970�. ������ ������ ��:
    - � ��������� �� ��� ����� - ���� �������� �������� � �����, ������ �� ��������� ������ � 16 ���� �� �������� �����:
        5 ����, ����� �� ����� ���������� �� ����� (0-31)
        4 ����, ����� �� ����� ���������� �� �������� (0-15)
        6 ����, ����� �� ����� ���������� �� �������� (0-63)
    - ��� ������������ � ��������� ��� ���� ����� (���, �����, ������), � ���� �������� ��� � ������� ������ dd/mm/yyyy
    - ��������� ����� print, ����� ������� ���� � ��������� ��-���� ������ �� ������� ���� ��������� ������� �����
    - ��� ��������� ������ �� ������ �� �������.
*/
#include <iostream>

class Date {

public:
    Date();
    Date(uint32_t day, uint32_t month, uint32_t year);
    Date(const char* date);

    Date(const Date& other);
    Date& operator=(const Date& other);

    uint32_t getDay() const { return date & DAY_MASK; }
    uint32_t getMonth() const { return (date >> 5) & MONTH_MASK; }
    uint32_t getYear() const { return START_YEAR +((date >> 9) & YEAR_MASK); }

    int equals(const Date& other) const;
    bool print(std::ostream& os = std::cout) const;

private:
    static char* readString(const char*& str, int delim);
    static uint32_t parse(char* str);

private:
    static bool isValid(uint32_t day, uint32_t month, uint32_t year);

private:
    uint16_t date;

    const int DAY_MASK = 31;
    const int MONTH_MASK = 15;
    const int YEAR_MASK = 63;
    const int START_YEAR = 1970;
};