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
	void showAll() {
        for(int i = 0; i < validCommands.size(); i++) {
            std::cout << validCommands[i] << " ";
        }
        std::cout << std::endl;
    }

private:
	std::vector<std::string> validCommands;
};

#endif /* COMMANDWORDS_H */
