#pragma once
#include "Entity.h"
#include "Lightwall.h"
#include <vector>

class Bike :
    public Entity
{
public:
	struct Velocity
	{
		int x, y;
	};

	Bike() = default;
	Bike(int startX, int startY, int w, int h, int moveSpeed);
	Bike(int startX, int startY, int w, int h, int moveSpeed, SDL_Color color);

	bool changeVelocity(Velocity newVelocity);

	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;

private: 
	int moveSpeed;
	Velocity velocity;
	Lightwall currentTrailObj;

	std::vector<Lightwall> trailSegments;
	std::vector<Position> directionChangePositions;

	const Velocity ZERO = Velocity{ 0, 0 };
	const Velocity UP = Velocity{ 0, -1 };
	const Velocity DOWN = Velocity{ 0, 1 };
	const Velocity LEFT = Velocity{ -1, 0 };
	const Velocity RIGHT = Velocity{ 1, 0 };
};

