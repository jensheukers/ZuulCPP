// commandwords.h

#ifndef COMMANDWORDS_H
#define COMMANDWORDS_H

#include <iostream>
#include <vector>
#include <string>

class CommandWords
{
public:
	CommandWords();
	virtual ~CommandWords();

	bool isCommand(std::string);
	std::vector<std::string> getAll() {

		std::vector<std::string> commands;
        for(int i = 0; i < validCommands.size(); i++) {
			commands.push_back(validCommands[i]);
        }
		return commands;
    }

private:
	std::vector<std::string> validCommands;
};

#endif /* COMMANDWORDS_H */
