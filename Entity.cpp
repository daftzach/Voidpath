#include "Entity.h"
#include <SDL.h>

Entity::Entity(int x, int y, int w, int h)
{
	posX = x;
	posY = y;

	this->rect = new SDL_Rect {
		posX,
		posY,
		w,
		h
	};
}

void Entity::translate(int newX, int newY)
{
	// Set new logical position
	posX = newX;
	posY = newY;

	// Rectangle needs to move with logical position
	rect->x = posX;
	rect->y = posY;
}
