#pragma once
#include "GameState.h"
#include "Lightwall.h"
#include <vector>

class Bike;

struct SDL_Point;
struct SDL_Rect;
struct Direction;

class PlayState
	: public GameState
{
public:
	const int TILE_SIZE = 16;

	void start() override;
	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;

	void addLightwall(Lightwall lightwall);

private:
	bool shouldMove = true;

	Bike* player;
	std::vector<Lightwall> trailSegments;

	bool isColliding(Entity* entity1, Lightwall* entity2);
	void handleCollision(Entity* entity1, Entity* entity2);
};

