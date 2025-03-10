#include<iostream>
#include<fstream>

// Да се напише функция, която връща броя редове във файл.
int main4() {

	std::ifstream file("Template_for_task_4.txt");
	if (!file.is_open()) {
		std::cerr << "Cannot open file!";
	}

	int lines = 0;
	char c = 0;
	while (!file.eof()){
		file.get(c);
		if (c == '\n') lines++;
	}
	lines++;

	std::cout << "The number of lines is --> " << lines;
	file.close();
	return 0;
}