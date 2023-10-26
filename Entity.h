#pragma once
#include <SDL.h>

class Entity
{
public:
	struct Position
	{
		int x, y;
	};

	Entity() = default;
	Entity(int x, int y, int w, int h);
	Entity(int x, int y, int w, int h, SDL_Color color);

	virtual void update(float deltaTime) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;

	virtual void onCollision(Entity* collidedWith) = 0;

	void translate(int newX, int newY);
	void resizeRect(int newW, int newH);
	void changeColor(SDL_Color newColor);

	Position getPosition();
	SDL_Rect* getRect();


protected:
	SDL_Rect rect = { 0, 0, 0, 0 };
	SDL_Color color = { 255, 255, 255, 255 };

private:
	Position position = { 0, 0 };
};

