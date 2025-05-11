#include "DynamicArray.hpp"

DynamicArray::DynamicArray()
	: _count(0), cap(INITIAL_CAP)
{
	data = new int32_t[cap]{};
}

DynamicArray::DynamicArray(const DynamicArray& other)
	: _count(other._count), cap(other.cap)
{
	data = new int32_t[cap]{};
	for (int i = 0; i < _count; i++)
		data[i] = other.data[i];

}
DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	if (this == &other) return *this;

	if (cap < other.cap){
		clear();
		data = new int32_t[other.cap]{};
	}

	_count = other._count;
	cap = other.cap;

	for (int i = 0; i < other._count; i++){
		data[i] = other.data[i];
	}

	return *this;
}

DynamicArray::~DynamicArray() {
	clear();
}

void DynamicArray::clear() {
	delete[] data;
}
bool DynamicArray::resize() {
	int32_t* old = data;

	data = new(std::nothrow) int32_t[cap * 2];
	if (!data) {
		data = old;
		return false;
	}

	for (int i = 0; i < cap; i++){
		data[i] = old[i];
	}

	delete[] old;
	cap *= 2;
	return true;
}

int32_t DynamicArray::operator[](int32_t index) const {
	if (index < 0 || index >= cap) throw std::out_of_range("invalid index!");

	return data[index];
}
int32_t& DynamicArray::operator[](int32_t index) {
	if (index < 0 || index >= cap) throw std::out_of_range("invalid index!");

	return data[index];
}

DynamicArray& DynamicArray::operator+=(int32_t element) {
	if (_count + 1 >= cap) {
		if (!resize()) {
			clear();
			throw std::bad_alloc();
		}
	}

	data[_count++] = element;
	return *this;
}
DynamicArray operator+(const DynamicArray& arr, int32_t element) {
	DynamicArray copy(arr);

	copy += element;
	return copy;
}

DynamicArray& DynamicArray::operator+=(const DynamicArray& arr) {
	while (_count + arr._count >= cap) {
		if (_count + 1 >= cap)
			if (!resize()) {
				clear();
				throw std::bad_alloc();
			}
	}

	for (int i = 0; i < arr._count; i++)
	{
		data[_count++] = arr[i];
	}
	return *this;
}
DynamicArray operator+(const DynamicArray& arr1, const DynamicArray& arr2) {
	DynamicArray copy(arr1);

	copy += arr2;
	return copy;
}

DynamicArray& DynamicArray::operator-=(int32_t element) {

	int32_t* indexes = new int32_t[_count]; int32_t iter = 0;
	for (int i = 0; i < _count; i++)
		if (data[i] == element) indexes[iter++] = i;

	for (int i = 0; i < iter; i++)
	{
		for (int ii = indexes[i]; ii < _count - 1; ii++)
		{
			data[ii] = data[ii + 1];
		}
		data[_count - 1] = 0; // cleaning up

		--_count;
		for (int j = i + 1; j < iter; j++) indexes[j] -= 1;
	}

	delete[] indexes;
	return *this;
}
DynamicArray operator-(const DynamicArray& arr, int32_t element) {
	DynamicArray copy(arr);

	copy -= element;
	return copy;
}

bool operator<(const DynamicArray& a1, const DynamicArray& a2) {
	int len1 = a1.count();
	int len2 = a2.count();

	int less = len1 < len2 ? len1 : len2;
	for (int i = 0; i < less; i++){
		if (a1[i] == a2[i]) continue;

		if (a1[i] < a2[i]) return true;
		return false;
	}

	return len1 < len2 ? true : false;
}
bool operator<=(const DynamicArray& a1, const DynamicArray& a2) {
	return a1 < a2 || a1 == a2;
}

bool operator>(const DynamicArray& a1, const DynamicArray& a2) {
	return !(a1 < a2);
}
bool operator>=(const DynamicArray& a1, const DynamicArray& a2) {
	return a1 > a2 || a1 == a2;
}

bool operator==(const DynamicArray& a1, const DynamicArray& a2) {
	if (a1.count() != a2.count()) return false;

	int len = a1.count();
	for (int i = 0; i < len; i++){
		if (a1[i] != a2[i]) return false;
	}
}
bool operator!=(const DynamicArray& a1, const DynamicArray& a2) {
	return !(a1 == a2);
}

std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
	if (!os) throw std::invalid_argument("bad stream!");

	for (int i = 0; i < arr._count && os; i++){
		os << arr[i];
		if(i + 1 < arr._count) os << ' ';
	}

	std::cout << '\n';
	return os;
}
std::istream& operator>>(std::istream& is, DynamicArray& arr) {
	if (!is) throw std::invalid_argument("bad stream!");

	char buffer[1024];
	is.getline(buffer, sizeof(buffer));
	if (!is) throw std::invalid_argument("bad stream!");

	int iter = 0;
	do{

		if (buffer[iter] >= '0' && buffer[iter] < '9') {
			int num = 0;
			while (buffer[iter] >= '0' && buffer[iter] < '9')
			{
				num *= 10;
				num += buffer[iter] - '0';
				++iter;
			}
			arr[arr._count++] = num;
		}
	}while (buffer[iter] != '\0' && ++iter);

	return is;
}

int32_t DynamicArray::operator()(int32_t element) {
	for (int i = 0; i < _count; i++)
		if (data[i] == element) return i;

	return -1;
}