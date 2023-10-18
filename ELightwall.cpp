#include "ELightwall.h"
#include <SDL.h>

ELightwall::ELightwall(SDL_Rect rect)
{
	this->rect = rect;
	translate(rect.x, rect.y);
}

ELightwall::ELightwall(SDL_Rect rect, SDL_Color color)
	: ELightwall(rect)
{
	this->color = color;
}

void ELightwall::update(float deltaTime)
{
	//Entity::update(deltaTime);
}

void ELightwall::draw(SDL_Renderer* renderer)
{
	Entity::draw(renderer);
}
