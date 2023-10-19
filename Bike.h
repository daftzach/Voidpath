#pragma once
#include "Entity.h"

struct Direction
{
	int xDir;
	int yDir;
};
void clamp(Direction& direction, int minX, int maxX, int minY, int maxY);

enum MoveState
{
	STATE_STILL,
	STATE_UP,
	STATE_DOWN,
	STATE_LEFT,
	STATE_RIGHT
};

class Bike :
    public Entity
{
public:
	Bike() = default;
	Bike(int startX, int startY, int w, int h, int moveSpeed);
	Bike(int startX, int startY, int w, int h, int moveSpeed, SDL_Color color);

	bool changeDirection(Direction newDirection);
	MoveState getCurrentState();

	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;

private: 
	Direction currDirection = { 0, 0 };
	MoveState currState = STATE_STILL;
	int moveSpeed = 0;
};

