// parser.h

#ifndef PARSER_H
#define PARSER_H

#include "command.h"
#include "commandwords.h"

class Parser
{
public:
	Parser();
	virtual ~Parser();

	Command getCommand();
	std::vector<std::string> getCommands() { return commands.getAll(); }

private:
	CommandWords commands;
};

#endif /* PARSER_H */
