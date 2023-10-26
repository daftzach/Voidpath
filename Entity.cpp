#include "Entity.h"

Entity::Entity(int x, int y, int w, int h)
{
	position.x = x;
	position.y = y;

	this->rect = SDL_Rect{
		position.x,
		position.y,
		w,
		h
	};
}

Entity::Entity(int x, int y, int w, int h, SDL_Color color)
	: Entity(x, y, w, h)
{
	changeColor(color);
}

Entity::Position Entity::getPosition()
{
	return position;
}

SDL_Rect* Entity::getRect()
{
	return &rect;
}

void Entity::translate(int newX, int newY)
{
	if (newX != NULL) {
		position.x = newX;
		rect.x = position.x;
	}

	if (newY != NULL) {
		position.y = newY;
		rect.y = position.y;
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

void Entity::changeColor(SDL_Color newColor)
{
	this->color = newColor;
}


void Entity::draw(SDL_Renderer* renderer)
{
	// TODO: add setcolor method
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
	//SDL_RenderDrawRect(renderer, &rect);
}