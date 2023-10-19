#include "Lightwall.h"
#include <SDL.h>

Lightwall::Lightwall(SDL_Rect rect)
{
	this->rect = rect;
	translate(rect.x, rect.y);
}

Lightwall::Lightwall(SDL_Rect rect, SDL_Color color)
	: Lightwall(rect)
{
	this->color = color;
}

void Lightwall::update(float deltaTime)
{
	//Entity::update(deltaTime);
}

void Lightwall::draw(SDL_Renderer* renderer)
{
	Entity::draw(renderer);
}
