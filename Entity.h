#pragma once
struct SDL_Rect;
struct SDL_Renderer;

class Entity
{
public:
	Entity() = default;
	Entity(int x, int y, int w, int h);

	virtual void update(float deltaTime) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;

protected:
	void translate(int newX, int newY);

	int posX = 0;
	int posY = 0;
	SDL_Rect* rect = {};
};

