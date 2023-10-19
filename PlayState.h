#pragma once
#include "GameState.h"
#include "Lightwall.h"
// TODO: implement own data structure?
#include <vector>

class Bike;

struct SDL_Point;
struct SDL_Rect;
struct Direction;

class PlayState
	: public GameState
{
public:
	void start() override;
	void processEvents(SDL_Event& event) override;
	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;
	void dispose() override;

private:
	const int TILE_SIZE = 16;

	void processDirectionChange(Direction newDirection);

	Bike* player;
	std::vector<SDL_Point> dirChangeCoords = {};
	std::vector<Lightwall> lightwalls = {};
};

