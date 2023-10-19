#include "Bike.h"
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

Bike::Bike(int startX, int startY, int w, int h, int moveSpeed)
	: Entity(startX, startY, w, h)
	, moveSpeed(moveSpeed)
{
	rect = SDL_Rect {
		startX,
		startY,
		w,
		h
	};

	currState = STATE_STILL;
}

Bike::Bike(int startX, int startY, int w, int h, int moveSpeed, SDL_Color color)
	:Bike(startX, startY, w, h, moveSpeed)
{
	this->color = color;
}

bool Bike::changeDirection(Direction newDirection)
{
	//Clamp x and y direction values to between -1 and 1
	clamp(newDirection, -1, 1, -1, 1);

	if (currDirection.yDir == 0 && newDirection.yDir != 0) {
		currDirection.yDir = newDirection.yDir;
		currDirection.xDir = 0;

		switch (newDirection.yDir) {
		case -1:
			currState = STATE_UP;
			break;
		case 1:
			currState = STATE_DOWN;
			break;
		}

		return true;

	} else if (currDirection.xDir == 0 && newDirection.xDir != 0) {
		currDirection.xDir = newDirection.xDir;
		currDirection.yDir = 0;

		switch (newDirection.xDir) {
		case -1:
			currState = STATE_LEFT;
			break;
		case 1:
			currState = STATE_RIGHT;
			break;
		}

		return true;
	}

	// TODO: return error, log
	return false;
}

MoveState Bike::getCurrentState()
{
	return currState;
}

void Bike::update(float deltaTime)
{
	int newX = posX + (int)(currDirection.xDir * deltaTime * moveSpeed);
	int newY = posY + (int)(currDirection.yDir * deltaTime * moveSpeed);

	translate(newX, newY);
}

void Bike::draw(SDL_Renderer* renderer)
{
	Entity::draw(renderer);
}