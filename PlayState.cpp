#include "PlayState.h"
#include "Bike.h"
#include <SDL.h> 

// TODO: There's a better place to put these but keep them here for now
const Direction UP = { 0, -1 };
const Direction DOWN = { 0, 1 };
const Direction LEFT = { -1, 0 };
const Direction RIGHT = { 1, 0 };

const SDL_Color PLAYER_HEAD_COLOR = SDL_Color { 255, 255, 255, 255 };
const SDL_Color PLAYER_WALL_COLOR = SDL_Color{ 0, 0, 255, 255 };

void PlayState::start()
{
	// TODO: don't want to set size or start pos or move speed like this, of course
	player = new Bike(0, 0, TILE_SIZE, TILE_SIZE, 200, PLAYER_HEAD_COLOR);
}

void PlayState::processEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			processDirectionChange(UP);
			break;
		case SDLK_s:
			processDirectionChange(DOWN);
			break;
		case SDLK_a:
			processDirectionChange(LEFT);
			break;
		case SDLK_d:
			processDirectionChange(RIGHT);
			break;
		}
	}
}

void PlayState::update(float deltaTime)
{
	player->update(deltaTime);

	// TODO: MOVE to player and bike classes since bikes have to have lightwalls
	switch (player->getCurrentState()) {
	case STATE_UP:
		lightwalls.back().resizeRect(NULL, (dirChangeCoords.back().y + TILE_SIZE) - player->getPositionCoords().y);
		lightwalls.back().translate(NULL, player->getPositionCoords().y);
		break;
	case STATE_DOWN:
		lightwalls.back().resizeRect(NULL, player->getPositionCoords().y - dirChangeCoords.back().y);
		break;
	case STATE_LEFT:
		lightwalls.back().resizeRect((dirChangeCoords.back().x + TILE_SIZE) - player->getPositionCoords().x, NULL);
		lightwalls.back().translate(player->getPositionCoords().x, NULL);
		break;
	case STATE_RIGHT:
		lightwalls.back().resizeRect(player->getPositionCoords().x - dirChangeCoords.back().x, NULL);
		break;
	}
}

void PlayState::draw(SDL_Renderer* renderer)
{
	for (Lightwall lightwall : lightwalls) {
		lightwall.draw(renderer);
	}

	player->draw(renderer);
}

void PlayState::dispose()
{
	dirChangeCoords.clear();
	lightwalls.clear();
}

// TODO: MOVE to player and bike classes
void PlayState::processDirectionChange(Direction newDirection)
{
	SDL_Rect newLightwallRect = {};

	if (player->changeDirection(newDirection)) {
		dirChangeCoords.push_back(player->getPositionCoords());

		newLightwallRect.w = TILE_SIZE;
		newLightwallRect.h = TILE_SIZE;

		newLightwallRect.x = dirChangeCoords.back().x;
		newLightwallRect.y = dirChangeCoords.back().y;

		lightwalls.push_back(Lightwall(newLightwallRect, PLAYER_WALL_COLOR));
	}
}
