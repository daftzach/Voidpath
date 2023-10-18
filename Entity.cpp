#include "Entity.h"

Entity::Entity(int x, int y, int w, int h)
{
	posX = x;
	posY = y;

	this->rect = SDL_Rect{
		posX,
		posY,
		w,
		h
	};
}

Entity::Entity(int x, int y, int w, int h, SDL_Color color)
	: Entity(x, y, w, h)
{
	this->color = color;
}

void Entity::translate(int newX, int newY)
{
	if (newX != NULL) {
		posX = newX;
		rect.x = posX;
	}

	if (newY != NULL) {
		posY = newY;
		rect.y = posY;
	}
}

// Allowed to set to NULL in case w or h should not change
void Entity::resizeRect(int newW, int newH)
{
	if (newW != NULL) {
		rect.w = newW;
	}

	if (newH != NULL) {
		rect.h = newH;
	}
}

void Entity::draw(SDL_Renderer* renderer)
{
	// TODO: add setcolor method
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

SDL_Point Entity::getPositionCoords()
{
	return SDL_Point{ posX, posY };
}