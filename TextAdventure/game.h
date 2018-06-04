// game.h

#ifndef GAME_H
#define GAME_H

#include <string>

#include "parser.h"
#include "command.h"
#include "room.h"
#include "player.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void play();

private:
	void goRoom(Command command);
	void grab(Command command);
	void consume(Command command);
	void drop(Command command);
	void createRooms();
	bool processCommand(Command cmd);
	void printWelcome();
	void printHelp();

	Parser parser;
	Player player;

	Room* destroyedBase;
	Room* destroyedBaseBasement;
};

#endif /* GAME_H */
