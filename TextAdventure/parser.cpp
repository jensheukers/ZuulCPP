// parser.cpp
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{

}


Command Parser::getCommand() {
	// display command prompt
	std::cout << "> ";

	// get a full line of input
	std::string input;
	std::getline( std::cin, input );

	// split full input line into words
	std::vector<std::string> words; // empty list
	std::stringstream stringStream(input); // convert input to stream
	std::string word; // local word
	while(std::getline(stringStream, word, ' ')) { // while there are words...
		words.push_back(word); // add word to list
	}

	// /* display single word per line for debugging */
	// for (size_t i = 0; i < words.size(); i++) {
	// 	std::cout << "- " << words[i] << std::endl;
	// }

	if (words.size() == 0) { return Command(); } // list is empty

	if(commands.isCommand(words[0])) {
		// check words and return command
		if (words.size() > 1) { return Command(words[0], words[1]); } // there is a second word
		if (words.size() > 0) { return Command(words[0]); } // there is a single command word
	}

	return Command();
};
