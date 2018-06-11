#include "stdafx.h"
#include "writer.h";

void Writer::printLine(std::string line) {
	std::cout << line << std::endl;
}

void Writer::printSpc() {
	std::cout << std::endl;
}

void Writer::printLongLine() {
	std::cout << "_______________________________________________________________________________" << std::endl;
}

std::string Writer::append(std::string original, std::string append) {
	return original.append(append);
}