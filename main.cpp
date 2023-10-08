#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* args[])
{

	bool quit = false;
	SDL_Event e;

	// TODO: move
	SDL_Point playerPos;
	SDL_Point playerVelocity;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to initialize. SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("SnakeBike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("SDL Window failed to initialize. SDL_Error: %s\n", SDL_GetError());
		return -1;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("SDL Renderer failed to initialize. SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

	// TODO: move
	playerPos = {
		0,
		0
	};
	playerVelocity = {
		0,
		1
	};

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			// TODO: move
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_w:
					if (playerVelocity.y == 0) {
						playerVelocity.y = -1;
						playerVelocity.x = 0;
					}
					break;
				case SDLK_s:
					if (playerVelocity.y == 0) {
						playerVelocity.y = 1;
						playerVelocity.x = 0;
					}
					break;
				case SDLK_a:
					if (playerVelocity.x == 0) {
						playerVelocity.x = -1;
						playerVelocity.y = 0;
					}
					break;
				case SDLK_d:
					if (playerVelocity.x == 0) {
						playerVelocity.x = 1;
						playerVelocity.y = 0;
					}
					break;
				}
			}
		}

		// TODO: move
		// TODO: fix timestep
		playerPos.x += playerVelocity.x;
		playerPos.y += playerVelocity.y;

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		// TODO: move
		SDL_Rect playerRect = {
			playerPos.x,
			playerPos.y,
			24,
			24
		};
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &playerRect);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
