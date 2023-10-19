#include "Game.h"

int main(int argc, char* args[])
{
	Game game;
	game.init(1280, 720);
	game.update();
	game.close();
}