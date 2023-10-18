#pragma once
#include "Entity.h"

class ELightwall :
    public Entity
{
public:
    ELightwall(SDL_Rect rect);
    ELightwall(SDL_Rect rect, SDL_Color color);

    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
};

