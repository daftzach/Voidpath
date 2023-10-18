#pragma once
#include <SDL.h>

class Entity
{
public:
	Entity() = default;
	Entity(int x, int y, int w, int h);
	Entity(int x, int y, int w, int h, SDL_Color color);

	virtual void update(float deltaTime) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;

	void translate(int newX, int newY);
	void resizeRect(int newW, int newH);

	SDL_Point getPositionCoords();
protected:
	int posX = 0;
	int posY = 0;

	SDL_Rect rect = { 0, 0, 0, 0 };
	SDL_Color color = { 255, 255, 255, 255 };
};

