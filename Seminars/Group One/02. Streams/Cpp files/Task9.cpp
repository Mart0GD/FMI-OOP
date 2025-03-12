#include <iostream>
#include <fstream>
/*
Да се напише програма, която играе играта "Бесенка" (hangman). Думите, с които може
да се играе да са записани в текстов файл, по една на ред. Не се изисква никакъв
графичен или псевдографичен изход.
*/

#define HANGMAN_WORDS "Hangman.txt"
#define LETTER_BUFFER 128
#define LIVES 10


#pragma warning(disable: 4996)

char* getRandomWord(std::ifstream& stream);
void play(char*& word, size_t len);
char** getWords(std::ifstream& stream, int& count);
int getLines(std::ifstream& stream);
char* toLower(const char* word, size_t len);
void freeMat(char** matrix, size_t size);


int main() {
	std::ifstream stream(HANGMAN_WORDS);
	if (!stream.is_open()) {
		std::cerr << "Cannot open file for reading!";
		return -1;
	}

	char* word = getRandomWord(stream);
	if (!word) return -1;

	stream.close();
	play(word, strlen(word));
	return 0;
}

void play(char*& word, size_t len)
{
	char* wordCopy = toLower(word, len);
	if (!wordCopy) return;

	char* visual = new(std::nothrow) char[len + 1];
	if (!visual) return;
	for (int i = 0; i < len; i++) visual[i] = '*';
	visual[len] = '\0';

	int lives = LIVES;
	char ch = ' ';
	char* ptr = NULL;
	while (strchr(visual, '*') != NULL) {
		std::cout << visual << '\n' << "Enter a letter --> ";
		std::cin >> ch;
		ptr = strchr(wordCopy, ch);
		if(!ptr){
			if (--lives == 0) {
				break;
			}
			std::cout << "Word doesn't contain letter " << lives << " remaining!\n";
			continue;
		}

		while (ptr){
			int index = ptr - wordCopy;
			visual[index] = ch;
			wordCopy[index] = '*';

			ptr = strchr(wordCopy, ch);
		}
	}

	std::cin.ignore();
	if (lives > 0) std::cout << "\nCongratulations you guessed the word! - " << word << '\n' << "\nPlay again (press y)? --> \n";
	else std::cout << "\nYou got hanged!\n" << "\nPlay again (press y)? --> ";
	std::cin >> ch;

	delete[] visual;
	delete[] word;
	delete[] wordCopy;

	word = nullptr;
	visual = nullptr;
	wordCopy = nullptr;
	if (ch == 'y') main();
	std::cout << "\nGoobye!";
}

char* getRandomWord(std::ifstream& stream) {
	srand(time(NULL));

	int wordsCount = getLines(stream);;
	int rnd = rand() % wordsCount;
	char** words = getWords(stream, wordsCount);
	if (!words) return NULL;

	char* word = new(std::nothrow) char[LETTER_BUFFER];
	if (!word) return NULL;
	strcpy(word, words[rnd]);

	freeMat(words, wordsCount);
	return word;
}

char** getWords(std::ifstream& stream, int& count) {
	int wordsCount = getLines(stream);
	if (wordsCount < 0) return NULL;

	char** words = new(std::nothrow) char* [wordsCount];
	if (!words) return NULL;

	for (int i = 0; i < wordsCount; i++){
		words[i] = new(std::nothrow) char[LETTER_BUFFER];
		if (!words[i]) {
			freeMat(words, i);
			return NULL;
		}
	}

	int iter = 0;
	while (!stream.eof()){
		stream.getline(words[iter], LETTER_BUFFER);
		if (!stream || !words[iter]) {
			freeMat(words, wordsCount);
			return NULL;
		}
		iter++;
	}

	stream.clear();
	stream.seekg(0, std::ios::beg);

	return words;
}

int getLines(std::ifstream& stream) {
	const size_t buffer = 1024;

	char* temp = new(std::nothrow) char[buffer];
	if (!temp) return -1;

	int lines = 0;
	while (!stream.eof()) {
		stream.getline(temp, buffer, '\n');
		if (!stream) return -1;
		lines++;
	}

	stream.clear();
	stream.seekg(0, std::ios::beg);
	delete[] temp;
	return lines;
}

char* toLower(const char* word, size_t len) {
	const int diff = 'a' - 'A';
	char* lower = new(std::nothrow) char[len + 1];
	if (!lower) return NULL;

	int iter = 0;
	while (*word != '\0'){
		if (*word >= 'A' && *word <= 'Z') {
			lower[iter++] = *word + diff;
		}
		else lower[iter++] = *word;
		word++;
	}
	lower[iter] = '\0';

	return lower;
}

void freeMat(char** matrix, size_t size) {
	for (int i = 0; i < size; i++){
		delete[] matrix[i];
		matrix[i] = nullptr;
	}

	delete[] matrix;
	matrix = nullptr;
}