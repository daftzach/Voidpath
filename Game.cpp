#include <SDL.h>
#include <SDL_ttf.h>
#include "Game.h"
#include "Screen.h"
#include "SGame.h"

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
	currScreen = new SGame();
	currScreen->start();

	return true;
}

void Game::close()
{
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);

	currScreen->dispose();

	SDL_Quit();
}

void Game::update()
{
	SDL_Event sdlEvent;

	float currentTime = 0;
	float prevTime = 0;

	while (!shouldQuit) {
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		while (SDL_PollEvent(&sdlEvent) != 0) {
			if (sdlEvent.type == SDL_QUIT) {
				shouldQuit = true;
			}
			currScreen->processEvents(sdlEvent);
		}

		currScreen->update(deltaTime);

		draw();
	}
}

void Game::draw()
{
	SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(sdlRenderer);

	currScreen->draw(sdlRenderer);

	SDL_RenderPresent(sdlRenderer);
}


