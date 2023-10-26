#pragma once
#include "Entity.h"

class Lightwall :
    public Entity
{
public:
    Lightwall() = default;
    Lightwall(SDL_Rect rect);
    Lightwall(SDL_Rect rect, SDL_Color color);

    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;

    void onCollision(Entity* collidedWith) override;
};

