#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

int main(int argc, char* args[]) {

	bool quit = false;
	SDL_Event e;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to initialize. SDL_Error: %s\n", SDL_GetError());
		return 1;
	}
	else {
		window = SDL_CreateWindow("SnakeBike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("SDL Window failed to initialize. SDL_Error: %s\n", SDL_GetError());
			return 1;
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_UpdateWindowSurface(window);
	}

	SDL_FreeSurface(screenSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
