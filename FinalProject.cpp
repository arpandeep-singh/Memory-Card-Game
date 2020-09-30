// FinalProject.cpp : Defines the entry point for the application.
//

#include "FinalProject.h"
#include "Game.h"

using namespace FinalProject;

int main()
{
	Game game;

	while (true) {
		bool playing = game.runGame();
		if (!playing)break;
	}
	return 0;
}
