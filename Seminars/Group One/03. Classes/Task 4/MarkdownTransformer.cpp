#include "MarkdownTransformer.hpp"
#include <fstream>
#include <assert.h>

#pragma warning(disable: 4996)

constexpr std::size_t MAX_ROW_SIZE{ 1024 };
const char HEADER_SYMBOL[] = "#";
const char ITALLIC_SYMBOL[] = "_";
const char BOLD_SYMBOL[] = "**";

// default ctor
MarkdownTransformer::MarkdownTransformer() : fileName(nullptr), linesCount(0), rows(nullptr) {};
MarkdownTransformer::MarkdownTransformer(const char* fileName) : fileName(copyString(fileName))
{
	std::ifstream is(fileName);
	if (!is.is_open()) throw std::invalid_argument("File cannot be opened for reading!");

	linesCount= getLines(is);
	if (linesCount <= 0) {
		is.close();
		throw "invalid file format!";
	}

	rows = createMatirx(linesCount, MAX_ROW_SIZE);
	if (!rows) {
		is.close();
		clearData();
		throw std::bad_alloc();
	}

	bool res = extractLines(rows, is, linesCount);
	if (!res) {
		is.close();
		clearData();
		throw "invalid input!";
	}

	is.close();
}

// copy 
MarkdownTransformer::MarkdownTransformer(const MarkdownTransformer& other) 
	:fileName(copyString(other.fileName)), linesCount(other.linesCount) {
	
	try {
		rows = createMatirx(linesCount, MAX_ROW_SIZE);
		if (!rows) throw;

		for (int i = 0; i < linesCount; i++)
			strcpy(rows[i], other.rows[i]);
	}
	catch(...) {
		this->clearData();
		throw "couldn't copy object!";
	}
}
MarkdownTransformer& MarkdownTransformer::operator=(const MarkdownTransformer& other){
	if (this == &other) return *this;

	char* fileNameTemp = nullptr;
	char** rowsTemp = nullptr;

	try
	{
		fileNameTemp = copyString(other.fileName); // throws 

		rowsTemp = createMatirx(other.linesCount, MAX_ROW_SIZE);
		if (!rows) throw; // throws

		for (int i = 0; i < linesCount; i++)
			rows[i] = other.rows[i];
	}
	catch (const std::exception&){
		delete[] fileNameTemp; fileNameTemp = nullptr;
		// matrix won't be allocated, it only signals on fail!

		throw "could't copy object!";
	}
	clearData();

	linesCount = other.linesCount;
	rows = rowsTemp;
	fileName = fileNameTemp;

	return *this;
}

// move
MarkdownTransformer::MarkdownTransformer(MarkdownTransformer&& other) noexcept{
	linesCount = other.linesCount;
	fileName = other.fileName;
	rows = other.rows;

	other.fileName = nullptr; other.fileName = nullptr;
}
MarkdownTransformer& MarkdownTransformer::operator=(MarkdownTransformer&& other) noexcept {
	if (this == &other) return *this;
	clearData();
	
	linesCount = other.linesCount;
	std::swap(fileName, other.fileName);
	std::swap(rows, other.rows);

	return *this;
}

MarkdownTransformer::~MarkdownTransformer() noexcept {
	clearData();
}

// public
bool MarkdownTransformer::makeHeading(std::size_t line) {
	if (!isValidIndex(line, linesCount)) return false;

	char* temp = new(std::nothrow) char[strlen(rows[line]) + 1 + strlen(HEADER_SYMBOL)];
	if (!temp) return false;

	strcpy(temp, HEADER_SYMBOL);
	strcpy(temp + strlen(HEADER_SYMBOL), rows[line]);

	delete[] rows[line];
	rows[line] = temp;

	return true;
}
bool MarkdownTransformer::makeItalic(std::size_t line, std::size_t from, std::size_t to) {
	if (!isValidIndex(line, linesCount) ||
		!isValidIndex(from, MAX_ROW_SIZE) ||
		!isValidIndex(to, MAX_ROW_SIZE) ||
		from > to) return false;

	char* temp = formatRow(line, from, to, ITALLIC_SYMBOL);
	if (!temp) return false;

	delete[] rows[line];
	rows[line] = temp;

	return true;
}
bool MarkdownTransformer::makeBold(std::size_t line, std::size_t from, std::size_t to) {
	if (!isValidIndex(line, linesCount) || 
		!isValidIndex(from, MAX_ROW_SIZE) || 
		!isValidIndex(to, MAX_ROW_SIZE) ||
		from > to) return false;

	char* temp = formatRow(line, from, to, BOLD_SYMBOL);
	if (!temp) return false;

	delete[] rows[line];
	rows[line] = temp;

	return true;
}
bool MarkdownTransformer::makeCombine(std::size_t line, std::size_t from, std::size_t to) {
	char* original = new(std::nothrow) char[strlen(rows[line]) + 1];
	if (!original) return false;
	original = strcpy(original, rows[line]);

	if (!makeBold(line, from, to)) {
		delete[] original; original = nullptr;
		return false;
	}
	if (!makeItalic(line, from + strlen(BOLD_SYMBOL), to + strlen(BOLD_SYMBOL))) {
		delete rows[line];
		rows[line] = original;
		return false;
	}

	delete[] original; original = nullptr;
	return true;
}
bool MarkdownTransformer::addLine(const char* content) {
	if (!content) return false;

	char** temp = createMatirx(linesCount + 1, MAX_ROW_SIZE);
	if (!temp) return false;

	for (int i = 0; i < linesCount; i++){
		if (!strcpy(temp[i], rows[i])) {
			clearMatrix(temp, i);
			return false;
		}
	}
	strcpy(temp[linesCount], content);

	clearMatrix(rows, linesCount);
	incrementLines();
	rows = temp;

	return true;
}
bool MarkdownTransformer::remove(std::size_t line) {
	if (line < 0 || line >= linesCount) return false;

	delete rows[line]; 
	for (int i = line; i < linesCount - 1; i++){
		rows[i] = rows[i + 1];
	}
	decrementLines();

	return true;
}
void MarkdownTransformer::exit() {
	int dotIndex = strchr(fileName, '.') - fileName;

	char* out = strncpy(new char[strlen(fileName)], fileName, dotIndex);
	out[dotIndex] = '\0';
	strcat(out, ".md");

	std::ofstream os(out, std::ios::out);
	if (!os.is_open()) return;
	
	for (int i = 0; i < linesCount; i++){
		os << rows[i];
		if (i + 1 != linesCount) os << '\n';
	}

	os.close();
}

// private 
int MarkdownTransformer::getLines(std::istream& is) {
	if (!is) return -1;

	int lines = 0;
	char ch = 0;
	int readChars = 0;
	while (is.get(ch)){
		if (!is) return -1;

		lines += ch == '\n';
		if (ch == '\n') readChars = 0;
		readChars++;
	}
	lines += readChars > 0 ? 1 : 0;

	is.clear();
	is.seekg(std::ios::beg);
	return lines;
}
bool MarkdownTransformer::extractLines(char** matrix, std::istream& is, int lines) {
	int line = 0;
	while (is) {
		if(!is.getline(matrix[line++], MAX_ROW_SIZE)) return false;
		if (is.eof()) break;
	}

	is.clear();
	is.seekg(std::ios::beg);
	return true;
}
bool MarkdownTransformer::moveStringRight(char*& str, int len, int index, std::size_t moves) {
	if (index < 0 || index > len || !str) return false;

	for (int i = 0; i < moves; i++){
		for (int i = len; i > index; i--) {
			str[i] = str[i - 1];
		}
	}
	
	str[len + moves] = '\0';
	return true;
}
bool MarkdownTransformer::isValidIndex(std::size_t index, std::size_t cap) {
	return index < cap && index >= 0;
}
char* MarkdownTransformer::formatRow(std::size_t line, std::size_t from, std::size_t to, const char symbol[]) {
	char* formatted = new(std::nothrow) char[MAX_ROW_SIZE];
	if (!formatted) return nullptr;
	
	strncpy(formatted, rows[line], from); formatted[from] = '\0';
	strcat(formatted, symbol);
	strncpy(formatted + strlen(formatted), rows[line] + from, to - from); formatted[from + strlen(symbol) + (to - from)] = '\0';
	strcat(formatted, symbol);
	strcpy(formatted + strlen(formatted), rows[line] + to);

	return formatted;
}
void MarkdownTransformer::clearData() {
	if(rows) clearMatrix(rows, linesCount);
	delete[] fileName;

	fileName = nullptr;
}
char** MarkdownTransformer::createMatirx(int rows, int cols) {
	if (rows < 0 || cols < 0) return nullptr;

	char** matrix = new(std::nothrow) char*[rows];
	if (!matrix) return matrix;

	for (int i = 0; i < rows; i++){
		matrix[i] = new(std::nothrow) char[cols];
		if (!matrix) {
			clearMatrix(matrix, i);
		}
	}

	return matrix;
}
void MarkdownTransformer::clearMatrix(char** matrix,std::size_t size) {
	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}

	delete[] matrix;
	matrix = nullptr;
}
bool MarkdownTransformer::set(char*& where, const char* what) {
	if (!what) return false;

	char* t = new(std::nothrow) char[strlen(what) + 1];
	if (!t) return false;
	strcpy(t, what);

	delete[] where;
	where = t;

	return true;
}
char* MarkdownTransformer::copyString(const char* what) {
	if (!what || !what[0]) throw std::invalid_argument("invalid string!");

	char* res = new char[strlen(what) + 1];
	return strcpy(res, what);
}