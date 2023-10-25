#include "PlayState.h"
#include "Bike.h"
#include <SDL.h> 

const SDL_Color PLAYER_HEAD_COLOR = SDL_Color { 255, 255, 255, 255 };

void PlayState::start()
{
	// TODO: don't want to set size or start pos or move speed like this, of course
	player = new Bike(0, 0, TILE_SIZE, TILE_SIZE, 200, PLAYER_HEAD_COLOR);
}

void PlayState::update(float deltaTime)
{
	player->update(deltaTime);
}

void PlayState::draw(SDL_Renderer* renderer)
{

	player->draw(renderer);
}