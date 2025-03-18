#include<iostream>
#include<fstream>

// Да се напише функция, която заменя всяко срещане на символ във файл с друг символ. Съдържанието на файла НЕ трябва да се зарежда в паметта.
int main() {
	char replace = -1;
	char replacer = -1;

	std::cout << "Insert (replace, replacer)--> ";
	do
	{
		std::cin >> replace >> replacer;
	} while (replace == -1 || replacer == -1);

	std::fstream file("Template_for_task_5.txt");
	if (!file.is_open()) {
		std::cerr << "Cannot open file!";
	}

	char ch = ' ';
	while (file){
		file >> ch;

		if (ch == replace){
			file.seekg(-1, std::ios::cur);
			file.put(replacer);
			file.flush();
		}
	}

	file.close();
	return 0;
}