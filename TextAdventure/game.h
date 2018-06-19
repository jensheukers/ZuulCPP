// game.h

#ifndef GAME_H
#define GAME_H

#include <string>

#include "items.h"
#include "weapons.h"
#include "parser.h"
#include "command.h"
#include "room.h"
#include "player.h"
#include "writer.h"
#include "enemys.h"


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
	void clear();
	void attack(Command cmd);
	void counterAttack();
	void equip(Command cmd);

	Parser parser;
	Player player;

	Room* prisonCell;
	Room* prisonCellUnder;

	Room* prisonCellBlockA;
	Room* prisonCellBlockB;
	Room* prisonCellBlockC;
	Room* celSoap;

	Room* cantina;

	Room* playGround;
	Room* armory;
	Room* shower;

	Room* wardenHallWay;
	Room* wardenRoom;
};

#endif /* GAME_H */
