#include "Touhou.h"
#include "Game.h"

int main(int argc, char* args[]) {
	Game game;

	game.load();
	game.run();
	
	return 0;
}
