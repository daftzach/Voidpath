#include "SGame.h"
#include "EBike.h"
#include <SDL.h>

void SGame::start()
{
	// TODO: don't want to set size or start pos or move speed like this, of course
	player = new EBike(0, 0, 16, 16, 200);
}

void SGame::processEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			player->changeDirection(Direction{ 0, -1 });
			break;
		case SDLK_s:
			player->changeDirection(Direction{ 0, 1 });
			break;
		case SDLK_a:
			player->changeDirection(Direction{ -1, 0 });
			break;
		case SDLK_d:
			player->changeDirection(Direction{ 1, 0 });
			break;
		}
	}
}

void SGame::update(float deltaTime)
{
	player->update(deltaTime);
}

void SGame::draw(SDL_Renderer* renderer)
{
	player->draw(renderer);
}

void SGame::dispose()
{
}
