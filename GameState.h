#pragma once

struct SDL_Renderer;

class GameState
{
public:
	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;
};

