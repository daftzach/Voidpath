#pragma once
#include "Entity.h"

class Lightwall :
    public Entity
{
public:
    Lightwall(SDL_Rect rect);
    Lightwall(SDL_Rect rect, SDL_Color color);

    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
};

