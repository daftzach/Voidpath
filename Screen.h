#pragma once

struct SDL_Renderer;
union SDL_Event;

class Screen
{
public:
	virtual void start() = 0;
	virtual void processEvents(SDL_Event& event) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;
	virtual void dispose() = 0;
};

