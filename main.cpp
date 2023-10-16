#include "Game.h"

int main(int argc, char* args[])
{
	Game game;
	game.init(1280, 720);
	game.update();
	game.close();
}

/*
* #include <SDL.h>
#include <stdio.h>
#include <vector>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);

bool checkCollision(SDL_Rect rectA, SDL_Rect rectB)
{
	// Sides of bounding boxes
	int leftRectA, leftRectB;
	int rightRectA, rightRectB;
	int topRectA, topRectB;
	int bottomRectA, bottomRectB;

	// RECT A
	leftRectA = rectA.x;
	rightRectA = rectA.x + rectA.w;
	topRectA = rectA.y;
	bottomRectA = rectA.y + rectA.h;

	// RECT B
	leftRectB = rectB.x;
	rightRectB = rectB.x + rectB.w;
	topRectB = rectB.y;
	bottomRectB = rectB.y + rectB.h;

	if (bottomRectA <= topRectB) {
		return false;
	}

	if (topRectA >= bottomRectB) {
		return false;
	}

	if (rightRectA <= leftRectB) {
		return false;
	}

	if (leftRectA >= rightRectB) {
		return false;
	}

	return true;
}

int main(int argc, char* args[])
{
	bool quit = false;
	SDL_Event e;

	// TODO: move
	SDL_Point playerPos;
	SDL_Point playerVelocity;

	// TODO: move? cleanup
	float frameTime = 0;
	float prevTime = 0;
	float currentTime = 0;
	float deltaTime = 0;

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


	SDL_GL_SetSwapInterval(-1);

	// TODO: move
	playerPos = {
		0,
		0
	};
	playerVelocity = {
		0,
		1
	};

	SDL_Rect playerRect = {
			playerPos.x,
			playerPos.y,
			16,
			16
	};

	// TODO: move
	// TODO: having two of these may not be needed. 
	// positionChangeRects could probably just become a vector of SDL_Points? may not even be needed in long run
	std::vector<SDL_Rect> positionChangeRects = { playerRect };
	std::vector<SDL_Rect> wallRects { playerRect };

	while (!quit) {
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		//printf("%f\n", (float)(1 / deltaTime));

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			//if (canMove) {
				if (e.type == SDL_KEYDOWN) {
					SDL_Rect newRect = {
							playerPos.x,
							playerPos.y,
							16,
							16
					};
					switch (e.key.keysym.sym) {
					// never allow consecutive move directions to be on the same axis.
					// add new position change rect when position change made, and begin construction of new lightwall
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
				//}
			}
		}

		// TODO: move
		frameTime += deltaTime;

		// TODO: move
		playerPos.x += (int)(playerVelocity.x * deltaTime * 200);
		playerPos.y += (int)(playerVelocity.y * deltaTime * 200);

		// TODO: move and create reset method for player(s)
		if (playerPos.x < 0 || playerPos.x > 1280 || playerPos.y < 0 || playerPos.y > 720) {
			positionChangeRects.clear();
			wallRects.clear();

			playerPos.x = 0;
			playerPos.y = 0;

			playerRect.x = 0;
			playerRect.y = 0;

			playerVelocity.x = 0;
			playerVelocity.y = 1;

			positionChangeRects.push_back(playerRect);
			wallRects.push_back(playerRect);
		}
		else if (wallRects.size() != 0) {
			// TODO: think of a better way to do this
			// This break doesn't seem like a good practice. 
			// Do NOT check current wall for collision (since it's not possible to collide with it)
			// -- otherwise the side of the player and wall that are SUPPOSED to be touching will always collide
			// hence, I use size instead of size + 1
			for (int i = 1; i < wallRects.size(); i++) {
				if (checkCollision(playerRect, wallRects[i - 1])) {
					//SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
					positionChangeRects.clear();
					wallRects.clear();

					playerPos.x = 0;
					playerPos.y = 0;

					playerRect.x = 0;
					playerRect.y = 0;

					playerVelocity.x = 0;
					playerVelocity.y = 1;

					positionChangeRects.push_back(playerRect);
					wallRects.push_back(playerRect);
					break;
				}
			}
		}

		// TODO: move

			current wall = wall being built in direction we are currently moving.
			previous wall = wall that was built in last direction we were moving.
			current wall needs to start at end of previous wall's rectangle and end at player's current position.

			previous wall end = previous wall width (if was moving vertically) or height (if was moving horizontally)
			current wall start (x, y) = previous wall end SDL_Point
			current wall end (width, height) = width or height are distance from current wall start (currentRect (x, y))

			SDL_Rect origin is top left

		if (positionChangeRects.size() != 0) {
			// new rectangle will be built from previous position change rect and modified based on current position
			// TODO: this can be condensed to newRect = back() but I am keeping this for now for clarity
			SDL_Rect newRect = {
				positionChangeRects.back().x,
				positionChangeRects.back().y,
				positionChangeRects.back().w,
				positionChangeRects.back().h,
			};

			// moving in y dir
			// 1 = down = positive
			if (playerVelocity.y == 1) {
				// the height of newRect is calculated from top of player rect to the origin of the rect that symbolizes our last position change
				// i.e. the distance from our previous direction change to the top of the player rect
				newRect.h = playerPos.y - positionChangeRects.back().y;
			}
			// -1 = up = negative
			else if (playerVelocity.y == -1) {
				// since we are moving up, rect origin needs to be on bottom of player rect to prevent false-positive collision
				// hence, I shift (add) 16 px down to move new rect origin right BELOW player rect
				// this is because origin is calculated at top left, and since we are oving up, we do not want origin to be the same as player rect origin
				// otherwise they are right on top of each other
				newRect.h = (positionChangeRects.back().y + positionChangeRects.back().w) - (playerPos.y + 16);
				newRect.y = playerPos.y + 16;
			}

			// moving in x dir
			// 1 = right = positive
			if (playerVelocity.x == 1) {
				// the width of newRect is calculated from left of player rect to the origin of the rect that symbolizes our last position change
				// i.e. the distance from our previous direction change to the left of the player rect
				newRect.w = playerPos.x - positionChangeRects.back().x;
			}
			// -1 = left = negative
			else if (playerVelocity.x == -1) {
				// since we are moving left, rect origin needs to be on right of player rect to prevent false-positive collision
				// hence, I shift (add) 16 px right to move new rect origin along right edge of player rect
				// this is because origin is calculated at top left, and since we are moving left, we do not want origin to be the same as player rect origin
				// otherwise they are right on top of each other
				newRect.w = (positionChangeRects.back().x + positionChangeRects.back().h) - (playerPos.x + 16);
				newRect.x = playerPos.x + 16;
			}

			// add the wall to the back of walls vector -- in other words this is the "current" wall 
			wallRects.back() = newRect;
		}


		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		// TODO: move
		//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		//for (SDL_Rect rect : positionChangeRects) {
			//SDL_RenderFillRect(renderer, &rect);
		//}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);

		for (SDL_Rect rect : wallRects) {
			SDL_RenderFillRect(renderer, &rect);
			//SDL_RenderDrawRect(renderer, &rect);
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		playerRect.x = playerPos.x;
		playerRect.y = playerPos.y;

		SDL_RenderFillRect(renderer, &playerRect);
		//SDL_RenderDrawRect(renderer, &playerRect);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
*/