#pragma once

struct SDL_Window;
struct SDL_Renderer;
class GameState;

class Game
{
public:
	// TODO: consts
	bool init(int windowWidth, int windowHeight);
	void close();
	void update();

private:
	void draw();

	bool shouldQuit = false;

	SDL_Window* sdlWindow = {};
	SDL_Renderer* sdlRenderer = {};

	GameState* currState;
};

