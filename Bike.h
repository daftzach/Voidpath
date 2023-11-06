#pragma once
#include "Entity.h"
#include "Lightwall.h"
#include <vector>

class PlayState;

class Bike :
    public Entity
{
public:
	struct Direction
	{
		float x, y;
	};

	Bike() = default;
	Bike(float startX, float startY, float w, float h, float moveSpeed);
	Bike(float startX, float startY, float w, float h, float moveSpeed, SDL_Color color);
	Bike(float startX, float startY, float w, float h, float moveSpeed, SDL_Color color, PlayState* world);

	bool changeDirection(Direction newVelocity);
	void reset();

	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;

private: 
	Position startPosition;
	Direction direction;
	// The current trail being built by player. NOT added to lightwall vector.
	// TODO: create a bounding box so other players can collide with currentTrailObj.
	Lightwall currentTrailObj;
	PlayState* world;

	float moveSpeed;
	bool isAlive;

	std::vector<Position> directionChangePositions;

	const Direction ZERO = Direction{ 0, 0 };
	const Direction UP = Direction{ 0, -1 };
	const Direction DOWN = Direction{ 0, 1 };
	const Direction LEFT = Direction{ -1, 0 };
	const Direction RIGHT = Direction{ 1, 0 };
};

