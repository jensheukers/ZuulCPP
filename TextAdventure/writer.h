#pragma once
#include <iostream>
#include <string>
class Writer {
public:
	static void printLine(std::string line);
	static void printText(std::string word);
	static void printSpc();
	static void printEmpty(int amount);
	static void printLongLine();
	static std::string append(std::string original, std::string append);
};