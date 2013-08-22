#include "Program.h"
#include "Game.h"

CL_ClanApplication application(&Program::main);

int Program::main(const std::vector<CL_String> &args)
{
	// Initialize ClanLib base components
	CL_SetupCore setupCore;

	// Initialize ClanLib display components
	CL_SetupDisplay setupDisplay;

	// Initialize OpenGL drivers
	CL_SetupGL setupGL;
	
	// Create window
	CL_DisplayWindowDescription desc("ForestFire", CL_Size(800, 600), true);
	CL_DisplayWindow window(desc);

	// Create world
	Game game(window);

	// Run main loop
	game.run();

	return 0;
}