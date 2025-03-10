#include<iostream>
#include<fstream>

int main2() {
	std::ifstream fileIn("Template_for_task_2.txt");
	std::ofstream fileOut("Task2_Ouput.txt");

	if (!fileIn.is_open() || !fileOut.is_open()) {
		std::cerr << "cannot open file!" << std::endl;
	}

	char c = ' ';
	while (fileIn.peek() != EOF){
		fileIn.get(c);
		fileOut << c;
	}

	fileIn.close();
	fileOut.close();
	return 0;
}