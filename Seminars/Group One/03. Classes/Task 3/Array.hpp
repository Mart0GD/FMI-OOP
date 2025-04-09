#ifndef ARRAY_HPP
#define ARRAY_HPP

#include<iostream>
#include<functional>

/*
������������ ���� Array, ����� ������������ ��������� ����� �� ���� �����. �� ���� ������ �� ������:

�� ��������� � �������� ���������� �� �� ������;
�� ��������� � ��������� ������� �� ������ (� ������) �������;
�� �������� ������� � ���� �� ������. ��� ���� ����� - �� �� �������;
�� �������� ��� ������ �� ���������;
�� �� ��������� � ��������� ���;
�� �� ���������� (���������� ����� �������� - ������� ������, ���������� �� �������� �������� - ��������);
�������� ��������� ��� ������ �� ������������ ����� �� ���������� - �������� ����������� �� �� ����� ���� ��� ������, �� ���� � ��������.
*/

class Array {

public:
	Array(uint32_t capacity);

	Array(const Array& other);
	Array& operator=(const Array& other);

	Array(Array&& other) noexcept;
	Array& operator=(Array&& other) noexcept;

	void append(int32_t element);
	bool setAtIndex(int32_t element, uint32_t index);

	uint32_t getSize() { return size; }
	int32_t getAtIndex(uint32_t index) const { return data[index]; }

	void print(std::ostream& os = std::cout ) const;
	int equals(const Array&);
	void sort();
	void filter(bool(*func)(int32_t));

	~Array();

private:
	void expand();

private:
	int32_t* data;
	uint32_t size;
	uint32_t capacity;

	bool sorted;
};

#endif