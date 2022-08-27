/**
 * @file main.cpp
 * @author Daniel Victoriano (@djose1164)
 * @brief 
 * @version 0.1
 * @date 2022-08-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "game.h"

int main(int argc, char *argv[])
{
	Game game;

	if (game.initialize())
		game.run_loop();

	game.shutdown();

	return 0;
}