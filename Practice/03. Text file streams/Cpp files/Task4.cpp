#include<iostream>
#include<fstream>
#include <limits>

// Да се напише функция, която връща броя редове във файл.
int main4() {

	std::ifstream file("Template_for_task_4.txt");
	if (!file.is_open()) {
		std::cerr << "Cannot open file!";
	}

	int lines = 0;
	while (file){
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (!file) break;
		lines++;
	}

	std::cout << "The number of lines is --> " << lines;
	file.close();
	return 0;
}