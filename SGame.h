#pragma once
#include "Screen.h"
#include "ELightwall.h"
// TODO: implement own data structure?
#include <vector>

class EBike;

struct SDL_Point;
struct SDL_Rect;
struct Direction;

class SGame
	: public Screen
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

	EBike* player;
	std::vector<SDL_Point> dirChangeCoords = {};
	std::vector<ELightwall> lightwalls = {};
};

