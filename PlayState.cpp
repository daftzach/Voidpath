#include "PlayState.h"
#include "Bike.h"
#include <SDL.h> 

const SDL_Color PLAYER_HEAD_COLOR = SDL_Color { 255, 255, 255, 255 };

void PlayState::start()
{
	trailSegments = {};

	// TODO: don't want to set size or start pos or move speed like this, of course
	player = new Bike(0.0f, 0.0f, TILE_SIZE, TILE_SIZE, 0.16f, PLAYER_HEAD_COLOR, this);
}

void PlayState::update(float deltaTime)
{
	if (shouldMove) {
		player->update(deltaTime);
	}

	if (trailSegments.size() != 0) {
		for (int i = 0; i < trailSegments.size() - 1; i++) {
			if (checkCollision(player, &trailSegments[i])) {
			}
		}
	}
}

void PlayState::draw(SDL_Renderer* renderer)
{
	if (trailSegments.size() != 0) {
		for (auto& segment : trailSegments) {
			segment.draw(renderer);
		}
	}
	player->draw(renderer);
}

void PlayState::addLightwall(Lightwall lightwall)
{
	trailSegments.emplace_back(lightwall);
}

bool PlayState::checkCollision(Entity* entity1, Lightwall* entity2)
{
	// Sides of bounding boxes
	float leftRectA, leftRectB;
	float rightRectA, rightRectB;
	float topRectA, topRectB;
	float bottomRectA, bottomRectB;

	// RECT A
	leftRectA = entity1->getRect()->x;
	rightRectA = entity1->getRect()->x + entity1->getRect()->w;
	topRectA = entity1->getRect()->y;
	bottomRectA = entity1->getRect()->y + entity1->getRect()->h;

	// RECT B
	leftRectB = entity2->getRect()->x;
	rightRectB = entity2->getRect()->x + entity2->getRect()->w;
	topRectB = entity2->getRect()->y;
	bottomRectB = entity2->getRect()->y + entity2->getRect()->h;

	if (bottomRectA <= topRectB) {
		return false;
	}

	if (topRectA >= bottomRectB) {
		return false;
	}

	if (rightRectA <= leftRectB) {
		return false;
	}

	if (leftRectA >= rightRectB) {
		return false;
	}

	return true;
}