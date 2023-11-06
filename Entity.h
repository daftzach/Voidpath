#pragma once
#include <SDL.h>

class Entity
{
public:
	struct Position
	{
		float x, y;
	};

	Entity() = default;
	Entity(float x, float y, float w, float h);
	Entity(float x, float y, float w, float h, SDL_Color color);

	virtual void update(float deltaTime) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;

	void translate(float newX, float newY);
	void resizeRect(float newW, float newH);
	void changeColor(SDL_Color newColor);

	Position getPosition();
	SDL_FRect* getRect();

protected:
	SDL_FRect rect = { 0, 0, 0, 0 };
	SDL_Color color = { 255, 255, 255, 255 };

private:
	Position position = { 0, 0 };
};

