#include "DynamicArray.hpp"

#pragma region Ctor 

DynamicArray::DynamicArray(int32_t size)
	:_size(size), _position(0), _data(nullptr)
{
	_data = new int32_t[size] {};
}

DynamicArray::DynamicArray(const DynamicArray& other)
	: DynamicArray(other._size)
{
	for (int i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}
	_position = other._position;
}
DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	if (other._size > _size) throw std::invalid_argument("Larger size than anticipated!");
	if (this == &other) return *this;

	DynamicArray copy(other);
	*this = std::move(copy);

	return *this;
}

DynamicArray::DynamicArray(DynamicArray&& other) noexcept
	: _size(other._size), _position(other._position)
{
	_data = other._data;

	other._data = nullptr;
	other._size = 0;
	other._position = 0;
}
DynamicArray& DynamicArray::operator=(DynamicArray&& other) noexcept {
	if (this == &other) return *this;

	std::swap(_data, other._data);
	_size = other._size;
	_position = other._position;

	return *this;
}

DynamicArray::~DynamicArray() {
	delete[] _data; _data = nullptr;
}
#pragma endregion

#pragma region Operators

// присвояване
DynamicArray& DynamicArray::operator=(const int32_t* arr) {
	if (!arr) return *this;
	std::memcpy(_data, arr, _size);
	return *this;
}

// adding int's
DynamicArray DynamicArray::operator+(int32_t element) {
	if (_position + 1 == _size) resize(_size);
	DynamicArray copy(*this);

	copy += element;
	return copy;
}
DynamicArray& DynamicArray::operator+=(int32_t element) {
	if (_position + 1 == _size) resize(_size);
	_data[_position++] = element;
	return *this;
}

//adding another Dynamic array
DynamicArray DynamicArray::operator+(const DynamicArray& other) {
	if (_position + (other._position + 1) == _size) {
		resize(other._position + 1 < _size
									? _size
									: (other._position + 1) * 2);
	}
	DynamicArray copy(*this);

	copy += other;
	return copy;
}
DynamicArray& DynamicArray::operator+=(const DynamicArray& other) {
	if (_position + (other._position + 1) == _size) {
		resize(other._position + 1 < _size
			? _size
			: (other._position + 1) * 2);
	}

	for (int i = 0; i < other._position; i++) {
		_data[_position++] = other._data[i];
	}

	return *this;
}

// removing all instances of element
DynamicArray DynamicArray::operator-(int32_t element) {
	if (this->operator()(element) == -1) return *this;
	DynamicArray copy(*this);

	copy -= element;
	return copy;
}
DynamicArray& DynamicArray::operator-=(int32_t element) {
	if (this->operator()(element) == -1) return *this;

	int* indexes = new(std::nothrow) int[_position];
	if (!indexes) throw std::bad_alloc();

	int iter = 0;
	for (int i = 0; i < _position; i++) {
		if (_data[i] == element) indexes[iter++] = i;
	}

	for (int i = 0; i < iter; i++) {
		for (int j = indexes[i] - i; j < _position; j++)
		{
			_data[j] = _data[j + 1];
		}
		_position--;
	}

	delete[] indexes;
	return *this;
}

int32_t DynamicArray::operator[](int32_t index) const {
	if (index < 0 || index >= _size) throw std::out_of_range("Index out of range!");

	return _data[index];
}
int32_t& DynamicArray::operator[](int32_t index)  {
	if (index < 0 || index >= _size) throw std::out_of_range("Index out of range!");
	return _data[index];
}

// output and input

std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
	if (!os) throw std::invalid_argument("bad stream!");

	for (int i = 0; i < arr.position(); i++){
		os << arr[i] << ' ';
	}
	os << std::endl;
}
std::istream& operator>>(std::istream& is, DynamicArray& arr) {
	if (!is) throw std::invalid_argument("bad stream!");

	char* buffer = new char[1024];
	is.getline(buffer, 1024, '\n');

	char* start = buffer;
	while (*buffer)
	{
		if (*buffer >= '0' && *buffer <= '9'){
			int number = 0;
			while (*buffer >= '0' && *buffer <= '9')
			{
				number *= 10;
				number += *buffer - '0';
				buffer++;
			}
			arr += number;
			continue;
		}

		buffer++;
	}

	delete[] start;
}

// functional operator
int32_t DynamicArray::operator()(int32_t element) const  {
	for (int i = 0; i < _position; i++){
		if (_data[i] == element) return i;
	}
	return -1;
}

// comparison

bool operator < (const DynamicArray& da1, const DynamicArray& da2) {
	int iter = 0;
	while (iter < da1.size() && iter < da2.size())
	{
		int index = iter; ++iter;
		if (da1[index] == da2[index]) continue;

		int diff = da1[index] - da2[index];
		return diff > 0 ? false : true;
	}

	return iter == da1.size() ? true : false;
}
bool operator <= (const DynamicArray& da1, const DynamicArray& da2) {
	return da1 < da2 || da1 == da2;
}

bool operator > (const DynamicArray& da1, const DynamicArray& da2) {
	return !(da1 < da2);
}
bool operator >= (const DynamicArray& da1, const DynamicArray& da2) {
	return da1 > da2 || da1 == da2;
}

bool operator == (const DynamicArray& da1, const DynamicArray& da2) {
	if (da1.size() != da2.size()) return false;

	int iter = 0;
	while (iter < da1.size()) {
		if (da1[iter] != da2[iter]) return false;
		++iter;
	}
	return true;
}
bool operator != (const DynamicArray& da1, const DynamicArray& da2) {
	return !(da1 == da2);
}

#pragma endregion

#pragma region Iterator

DynamicArray::Iterator& DynamicArray::Iterator::operator ++ () {
	++position;
	return *this;
}
DynamicArray::Iterator DynamicArray::Iterator::operator ++ (int) {
	DynamicArray::Iterator copy(*this);
	++(*this);

	return copy;
}

bool DynamicArray::Iterator::operator == (const Iterator& other) const {
	return position == other.position;
}
bool DynamicArray::Iterator::operator != (const Iterator& other) const {
	return !(*this == other);
}

int DynamicArray::Iterator::operator * () const {
	return *position;
}
int& DynamicArray::Iterator::operator * () {
	return *position;
}

#pragma endregion

bool DynamicArray::resize(uint32_t amount) {
	int32_t* old = _data;

	_data = new(std::nothrow) int32_t[_size + amount];
	if (!_data) {
		_data = old;
		return false;
	}

	for (int i = 0; i < _position; i++){
		_data[i] = old[i];
	}

	_size += amount;
	delete[] old; old = nullptr;
	return true;
}
