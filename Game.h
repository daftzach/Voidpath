#pragma once

struct SDL_Window;
struct SDL_Renderer;
class Screen;

class Game
{
public:
	const int TILE_SIZE = 16;
	
	// TODO: consts
	bool init(int windowWidth, int windowHeight);

	void close();

	void update();

private:
	void draw();

	SDL_Window* sdlWindow = {};
	SDL_Renderer* sdlRenderer = {};

	Screen* currScreen;

	bool shouldQuit = false;

	float deltaTime = 0.0f;
};

