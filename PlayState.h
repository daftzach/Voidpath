#pragma once
#include "GameState.h"
#include "Lightwall.h"

class Bike;

struct SDL_Point;
struct SDL_Rect;
struct Direction;

class PlayState
	: public GameState
{
public:
	void start() override;
	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;

private:
	const int TILE_SIZE = 16;

	Bike* player;
};

