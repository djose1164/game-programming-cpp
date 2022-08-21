#include "game.h"

int main(int argc, char *argv[])
{
	Game game;
	auto success = game.initialize();

	if (success)
		game.run_loop();
	game.shutdown();
	
	return 0;
}