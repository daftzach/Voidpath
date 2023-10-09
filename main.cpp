#include <SDL.h>
#include <stdio.h>
#include <vector>

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
	std::vector<SDL_Rect> positionChangeRects;
	std::vector<SDL_Rect> wallRects;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("SDL failed to initialize. SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("SnakeBike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		SDL_Log("SDL Window failed to initialize. SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		SDL_Log("SDL Renderer failed to initialize. SDL_Error: %s\n", SDL_GetError());
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

	SDL_Rect newRect = {
		playerPos.x,
		playerPos.y,
		24,
		24
	};

	positionChangeRects.push_back(newRect);
	wallRects.push_back(newRect);

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			// TODO: move
			if (e.type == SDL_KEYDOWN) {
				SDL_Rect newRect = {
						playerPos.x,
						playerPos.y,
						24,
						24
				};
				switch (e.key.keysym.sym) {
				case SDLK_w:
					if (playerVelocity.y == 0) {
						positionChangeRects.push_back(newRect);
						wallRects.push_back(newRect);
						playerVelocity.y = -1;
						playerVelocity.x = 0;
					}
					break;
				case SDLK_s:
					if (playerVelocity.y == 0) {
						positionChangeRects.push_back(newRect);
						wallRects.push_back(newRect);
						playerVelocity.y = 1;
						playerVelocity.x = 0;
					}
					break;
				case SDLK_a:
					if (playerVelocity.x == 0) {
						positionChangeRects.push_back(newRect);
						wallRects.push_back(newRect);
						playerVelocity.x = -1;
						playerVelocity.y = 0;
					}
					break;
				case SDLK_d:
					if (playerVelocity.x == 0) {
						positionChangeRects.push_back(newRect);
						wallRects.push_back(newRect);
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
		/*
			current wall = wall being built in direction we are currently moving.
			previous wall = wall that was built in last direction we were moving.
			current wall needs to start at end of previous wall's rectangle and end at player's current position.

			previous wall end = previous wall width (if was moving vertically) or height (if was moving horizontally)
			current wall start (x, y) = previous wall end SDL_Point
			current wall end (width, height) = width or height are distance from current wall start (currentRect (x, y))

			SDL_Rect origin is top left

		*/
		if (positionChangeRects.size() != 0) {
			SDL_Rect newRect = {
				positionChangeRects.back().x,
				positionChangeRects.back().y,
				positionChangeRects.back().w,
				positionChangeRects.back().h,
			};

			// moving in y dir
			// 1 = down = positive
			if (playerVelocity.y == 1) {
				newRect.h = playerPos.y - positionChangeRects.back().y;
			}
			// -1 = up = negative
			else if (playerVelocity.y == -1) {
				newRect.x = playerPos.x;
				newRect.y = playerPos.y;
				newRect.h = (positionChangeRects.back().y + positionChangeRects.back().w) - playerPos.y;
			}

			// moving in x dir
			// 1 = right = positive
			if (playerVelocity.x == 1) {
				newRect.w = playerPos.x - positionChangeRects.back().x;
			}
			// -1 = left = negative
			else if (playerVelocity.x == -1) {
				newRect.x = playerPos.x;
				newRect.y = playerPos.y;
				newRect.w = (positionChangeRects.back().x + positionChangeRects.back().h) - playerPos.x;
			}

			wallRects.back() = newRect;
		}

		// TODO: move
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		for (SDL_Rect rect : positionChangeRects) {
			SDL_RenderFillRect(renderer, &rect);
		}
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
		for (SDL_Rect rect : wallRects) {
			SDL_RenderDrawRect(renderer, &rect);
		}

		// TODO: move
		SDL_Rect playerRect = {
			playerPos.x,
			playerPos.y,
			24,
			24
		};
		SDL_RenderFillRect(renderer, &playerRect);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
