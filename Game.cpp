#include <SDL.h>
#include <SDL_ttf.h>
#include "Game.h"
#include "GameState.h"
#include "PlayState.h"

bool Game::init(int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("SDL failed to initialize.\nSDL_Error: %s\n", SDL_GetError());
		return false;
	}

	sdlWindow = SDL_CreateWindow("SnakeBike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (sdlWindow == NULL) {
		SDL_Log("SDL Window failed to initialize.\nSDL_Error: %s\n", SDL_GetError());
		return false;
	}

	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if (sdlRenderer == NULL) {
		SDL_Log("SDL Renderer failed to initialize.\nSDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// TODO: state machine/stack
	currState = new PlayState();
	currState->start();

	return true;
}

void Game::close()
{
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

void Game::update()
{
	SDL_Event sdlEvent;

	Uint64 currentTime = SDL_GetPerformanceCounter();
	Uint64 prevTime = 0;
	float deltaTime = 0;

	while (!shouldQuit) {
		prevTime = currentTime;
		currentTime = SDL_GetPerformanceCounter();
		deltaTime = ((currentTime - prevTime) * 1000 / (float)SDL_GetPerformanceFrequency());

		while (SDL_PollEvent(&sdlEvent) != 0) {
			if (sdlEvent.type == SDL_QUIT) {
				shouldQuit = true;
			}
		}

		currState->update(deltaTime);

		draw();
	}
}

void Game::draw()
{
	SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(sdlRenderer);

	currState->draw(sdlRenderer);

	SDL_RenderPresent(sdlRenderer);
}


