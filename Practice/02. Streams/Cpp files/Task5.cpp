#include<iostream>
#include<fstream>

// Да се напише функция, която заменя всяко срещане на символ във файл с друг символ. Съдържанието на файла НЕ трябва да се зарежда в паметта.
int main5() {
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

	char c = ' ';
	while (file.peek() != EOF){
		file.get(c);

		if (c == replace){
			file.seekg(-1, std::ios::cur);
			file.put(replacer);
			file.flush();
		}
	}

	file.close();
	return 0;
}