#include "Entity.h"

Entity::Entity(float x, float y, float w, float h)
{
	position.x = x;
	position.y = y;

	this->rect = SDL_FRect {
		position.x,
		position.y,
		w,
		h
	};
}

Entity::Entity(float x, float y, float w, float h, SDL_Color color)
	: Entity(x, y, w, h)
{
	changeColor(color);
}

Entity::Position Entity::getPosition()
{
	return position;
}

SDL_FRect* Entity::getRect()
{
	return &rect;
}

void Entity::translate(float newX, float newY)
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
void Entity::resizeRect(float newW, float newH)
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
	SDL_RenderFillRectF(renderer, &rect);
	//SDL_RenderDrawRect(renderer, &rect);
}