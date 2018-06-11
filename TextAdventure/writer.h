#pragma once
#include <iostream>
#include <string>
class Writer {
public:
	static void printLine(std::string line);
	static void printSpc();
	static void printLongLine();
	static std::string append(std::string original, std::string append);
};