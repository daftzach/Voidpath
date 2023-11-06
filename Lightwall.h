#pragma once
#include "Entity.h"

class Lightwall :
    public Entity
{
public:
    Lightwall() = default;
    Lightwall(SDL_FRect rect);
    Lightwall(SDL_FRect rect, SDL_Color color);

    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
};

