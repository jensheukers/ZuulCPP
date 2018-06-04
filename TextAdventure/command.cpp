// command.cpp
#include "stdafx.h"
#include "command.h"

Command::Command(std::string first, std::string second)
{
	this->commandWord = first;
	this->secondWord = second;
}

Command::~Command()
{

}

std::string Command::getCommandWord()
{
	return this->commandWord;
}

bool Command::isUnknown()
{
	if (this->commandWord.compare("") == 0) {
		return true;
	}
	return false;
}

std::string Command::getSecondWord()
{
	return this->secondWord;
}

bool Command::hasSecondWord()
{
	if (this->secondWord.compare("") == 0) {
		return false;
	}
	return true;
}
