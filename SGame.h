#pragma once
#include "Screen.h"

class EBike;

class SGame
	: public Screen
{
public:
	void start() override;
	void processEvents(SDL_Event& event) override;
	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;
	void dispose() override;

private:
	EBike* player;
};

