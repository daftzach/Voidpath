#pragma once
#include "Entity.h"

struct Direction
{
	int xDir;
	int yDir;
};
void clamp(Direction& direction, int minX, int maxX, int minY, int maxY);

class EBike :
    public Entity
{
public:
	EBike() = default;
	EBike(int startX, int startY, int w, int h, int moveSpeed);

	bool changeDirection(Direction newDirection);

	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;

private: 
	Direction currDirection = { 0, 0 };
	int moveSpeed = 0;
};

