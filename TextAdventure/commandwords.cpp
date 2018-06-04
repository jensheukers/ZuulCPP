// commandwords.cpp
#include "stdafx.h"
#include "commandwords.h"

CommandWords::CommandWords()
{
	validCommands.push_back("go");
	validCommands.push_back("quit");
	validCommands.push_back("help");
	validCommands.push_back("look");
	validCommands.push_back("grab");
	validCommands.push_back("inventory");
	validCommands.push_back("consume");
	validCommands.push_back("drop");
}

CommandWords::~CommandWords()
{

}

bool CommandWords::isCommand(std::string str)
{
	for (size_t i = 0; i < validCommands.size(); i++) {
		if (validCommands[i].compare(str) == 0) {
			return true;
		}
	}
	return false;
}
