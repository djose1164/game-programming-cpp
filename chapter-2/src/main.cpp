#include "game.h"

int main(int argc, char *argv[])
{
	Game game;
	const auto result{game.initialize()};

	if (result)
		game.run_loop();

	game.shutdown();

	return 0;
}