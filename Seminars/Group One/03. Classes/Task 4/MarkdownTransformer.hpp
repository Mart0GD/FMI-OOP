#pragma once
#ifndef MARKDOWN_TRANSFORMER_HPP
#define MARKDOWN_TRANSFORMER_HPP

#include <fstream>

class MarkdownTransformer
{
public:
	MarkdownTransformer();
	MarkdownTransformer(const char* fileName);

	MarkdownTransformer(const MarkdownTransformer& other);
	MarkdownTransformer& operator=(const MarkdownTransformer& other);

	MarkdownTransformer(MarkdownTransformer&& other) noexcept;
	MarkdownTransformer& operator=(MarkdownTransformer&& other) noexcept;

	~MarkdownTransformer() noexcept;

	void incrementLines() { linesCount++; }
	void decrementLines() { linesCount--; }
	std::size_t getRowSize(std::size_t index) { return strlen(rows[index]); }


	bool makeHeading(std::size_t line);
	bool makeItalic(std::size_t line, std::size_t from, std::size_t to);
	bool makeBold(std::size_t line, std::size_t from, std::size_t to);
	bool makeCombine(std::size_t line, std::size_t from, std::size_t to);
	bool addLine(const char* content);
	bool remove(std::size_t line);
	void exit();

private:
	char** createMatirx(int rows, int cols);
	int getLines(std::istream& is);
	bool extractLines(char** matrix, std::istream& is, int lines);
	bool moveStringRight(char*& str, int len, int index, std::size_t moves);
	bool isValidIndex(std::size_t index, std::size_t cap);
	char* formatRow(std::size_t line, std::size_t from, std::size_t to, const char symbol[]);
	void clearData();
	void clearMatrix(char** matrix, std::size_t size);
	bool set(char*& where, const char* what);
	char* copyString(const char* what);

private:
	char** rows;
	std::size_t linesCount;

	char* fileName;
};

#endif

