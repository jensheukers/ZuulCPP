#include "stdafx.h"
#include "writer.h"
#include <ctime>
#include <vector>

void Writer::printLine(std::string line) {
	std::cout << line << std::endl;
}

void Writer::printText(std::string word) {
	std::cout << word;
}

void Writer::printSpc() {
	std::cout << std::endl;
}

void Writer::printLongLine() {
	std::cout << "_______________________________________________________________________________" << std::endl;
}

void Writer::printEmpty(int amount) {
	for (int i = 0; i < amount; i++) {
		std::cout << " ";
	}
}

std::string Writer::append(std::string original, std::string append) {
	return original.append(append);
}