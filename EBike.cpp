#include "EBike.h"
#include <SDL.h>

void clamp(Direction& direction, int minX, int maxX, int minY, int maxY)
{
	// Clamp x (positive)
	if (direction.xDir > 1) {
		direction.xDir = 1;
	}

	// Clamp x (negative)
	if (direction.xDir < -1) {
		direction.xDir = -1;
	}

	// Clamp y (positive)
	if (direction.yDir > 1) {
		direction.yDir = 1;
	}

	// Clamp y (negative)
	if (direction.yDir < -1) {
		direction.yDir = -1;
	}
}

EBike::EBike(int startX, int startY, int w, int h, int moveSpeed)
	: Entity(startX, startY, w, h)
	, moveSpeed(moveSpeed)
{
	rect = new SDL_Rect{
		startX,
		startY,
		w,
		h
	};
}

bool EBike::changeDirection(Direction newDirection)
{
	//Clamp x and y direction values to between -1 and 1
	clamp(newDirection, -1, 1, -1, 1);

	if (currDirection.yDir == 0 && newDirection.yDir != 0) {
		currDirection.yDir = newDirection.yDir;
		currDirection.xDir = 0;

		return true;

	} else if (currDirection.xDir == 0 && newDirection.xDir != 0) {
		currDirection.xDir = newDirection.xDir;
		currDirection.yDir = 0;

		return true;
	}

	// TODO: return error, log
	return false;
}

void EBike::update(float deltaTime)
{
	int newX = posX + (int)(currDirection.xDir * deltaTime * moveSpeed);
	int newY = posY + (int)(currDirection.yDir * deltaTime * moveSpeed);

	translate(newX, newY);
}

void EBike::draw(SDL_Renderer* renderer)
{
	// TODO: add setcolor method
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, rect);
}