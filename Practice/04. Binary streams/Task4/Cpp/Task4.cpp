#include <cstring>
#include <fstream>
#include "BMP.hpp"

bool IsValid(BMPHeader header);
bool invert(std::ofstream& out, std::ifstream& in, const BMPHeader& header);
bool greyscale(std::ofstream& out, std::ifstream& in, const BMPHeader& header);

int main(int argc, char* args[]) {
	if (argc != 4) {
		std::cerr << "Arguments are less than expected. Should be: <inputFile> <outputFile> <action(inverted|greyscale>)" 
				  << std::endl;
	}
	char* inputFileName = args[1];
	char* outputFileName = args[2];
	char* action = args[3];

	std::ifstream inputFile(inputFileName, std::ios::binary);
	if (!inputFile.is_open()) {
		std::cerr << "Cannot open file for reading";
		return - 1;
	}

	std::ofstream outputFile(outputFileName,  std::ios::binary);
	if (!outputFile.is_open()) {
		std::cerr << "Cannot open file for writing";
		return -1;
	}


	BMPHeader header = {};
	inputFile.read(reinterpret_cast<char*>(&header), sizeof(header));
	if (!IsValid(header)) return -1;
	outputFile.write(reinterpret_cast<const char*>(&header), sizeof(header));

	if (strcmp(action, "inverted") == 0) invert(outputFile, inputFile, header);
	else greyscale(outputFile, inputFile, header);

	inputFile.close();
	outputFile.close();
	return 0;
}

bool IsValid(BMPHeader header) {
	return header.signature[0] == 'B' && header.signature[1] == 'M';
}

bool invert(std::ofstream& out, std::ifstream& in, const BMPHeader& header) {
	int rowSizeWithPadding = (header.width * 3 + 3) & ~3;

	out.seekp(header.pixelArrayOffset, std::ios::beg);
	in.seekg(header.pixelArrayOffset, std::ios::beg);

	for (int row = 0; row < header.height; row++){
		for (int col = 0; col < header.width; col++){
			char b, g, r;

			in.read(reinterpret_cast<char*>(&b), 1);
			in.read(reinterpret_cast<char*>(&g), 1);
			in.read(reinterpret_cast<char*>(&r), 1);

			b = 255 - b;
			g = 255 - g;
			r = 255 - r;

			out.write(reinterpret_cast<const char*>(&b), 1);
			out.write(reinterpret_cast<const char*>(&g), 1);
			out.write(reinterpret_cast<const char*>(&r), 1);
		}
		char padding[3] = { 0 };
		in.read(padding, rowSizeWithPadding - header.width * 3);
		out.write(padding, rowSizeWithPadding - header.width * 3);
	}

	return true;
}

bool greyscale(std::ofstream& out, std::ifstream& in, const BMPHeader& header) {
	int rowSizeWithPadding = (header.width * 3 + 3) & ~3;

	out.seekp(header.pixelArrayOffset, std::ios::beg);
	in.seekg(header.pixelArrayOffset, std::ios::beg);

	for (int row = 0; row < header.height; row++) {
		for (int col = 0; col < header.width; col++) {
			char b, g, r;

			in.read(reinterpret_cast<char*>(&b), 1);
			in.read(reinterpret_cast<char*>(&g), 1);
			in.read(reinterpret_cast<char*>(&r), 1);

			char grey = 0.299 * r + 0.587 * g + 0.114 * b;

			out.write(reinterpret_cast<const char*>(&grey), 1);
			out.write(reinterpret_cast<const char*>(&grey), 1);
			out.write(reinterpret_cast<const char*>(&grey), 1);
		}
		char padding[3] = { 0 };
		in.read(padding, rowSizeWithPadding - header.width * 3);
		out.write(padding, rowSizeWithPadding - header.width * 3);
	}

	return true;
}