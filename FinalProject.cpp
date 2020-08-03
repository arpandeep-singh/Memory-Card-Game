// FinalProject.cpp : Defines the entry point for the application.
//

#include "FinalProject.h"
#include "Game.h"

using namespace std;

int main()
{
	Game game;

	while (game.isRunning()) {
		//game.update();
		game.render();
	}
	return 0;
}
