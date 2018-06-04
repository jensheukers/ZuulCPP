// command.h

#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command
{
public:
	Command(std::string first = "", std::string second = "");
	virtual ~Command();

	std::string getCommandWord();
	bool isUnknown();
	std::string getSecondWord();
	bool hasSecondWord();

private:
	std::string commandWord;
	std::string secondWord;
};

#endif /* COMMAND_H */
