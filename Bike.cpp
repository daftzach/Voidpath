#include "Bike.h"
#include "Lightwall.h"
#include "PlayState.h"
#include <SDL.h>

Bike::Bike(int startX, int startY, int w, int h, int moveSpeed)
	: Entity(startX, startY, w, h)
	, moveSpeed(moveSpeed)
{
	rect = SDL_Rect {
		startX,
		startY,
		w,
		h
	};

	startPosition = Position{ startX, startY };
	direction = { 0, 0 };
	directionChangePositions = {};
}

Bike::Bike(int startX, int startY, int w, int h, int moveSpeed, SDL_Color color)
	:Bike(startX, startY, w, h, moveSpeed)
{
	this->color = color;
}

Bike::Bike(int startX, int startY, int w, int h, int moveSpeed, SDL_Color color, PlayState* world)
	:Bike(startX, startY, w, h, moveSpeed)
{
	this->world = world;
}

bool Bike::changeDirection(Direction newDirection)
{
	SDL_Rect newLightwallRect = {};

	// Can only change y-movement if we are not already moving in the y-direction
	// Otherwise it would be very easy to accidentally collide into yourself
	if (direction.y == 0 && newDirection.y != 0) {
		direction.y = newDirection.y;
		direction.x = newDirection.x;
	// Can only change x-movement if we are not already moving in the x-direction
	} else if (direction.x == 0 && newDirection.x != 0) {
		direction.x = newDirection.x;
		direction.y = newDirection.y;
	}
	else {
		return false;
	}
	
	// Want to draw actual currentTrail as a different color for debugging
	// So change color before adding to world
	currentTrailObj.changeColor(SDL_Color{ 125, 125, 255, 255 });
	world->addLightwall(currentTrailObj);

	newLightwallRect.w = rect.w;
	newLightwallRect.h = rect.h;
	newLightwallRect.x = getPosition().x;
	newLightwallRect.y = getPosition().y;
	
	directionChangePositions.push_back(getPosition());
	currentTrailObj = Lightwall(newLightwallRect, SDL_Color{255, 0, 0, 255});

	return true;
;}

void Bike::reset()
{
	direction = ZERO;
	translate(startPosition.x, startPosition.y);
}

void Bike::update(float deltaTime)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	/* Use else if statements because:
	As seperate if statements, it is too easy to collide with self.
	For instance, if you press S and D too quickly, a collision is detected due to
	the Lightwall being added upon successful input, on same position as player,
	since they are briefly in the same position. */
	if (currentKeyStates[SDL_SCANCODE_W]) {
		changeDirection(UP);
	} else if (currentKeyStates[SDL_SCANCODE_S]) {
		changeDirection(DOWN);
	} else if (currentKeyStates[SDL_SCANCODE_A]) {
		changeDirection(LEFT);
	} else if (currentKeyStates[SDL_SCANCODE_D]) {
		changeDirection(RIGHT);
	}

	int newX = getPosition().x + (int)((direction.x * moveSpeed * deltaTime));
	int newY = getPosition().y + (int)((direction.y * moveSpeed * deltaTime));
	translate(newX, newY);

	if (directionChangePositions.size() != 0) {
		if (direction.y < 0) {
			currentTrailObj.resizeRect(NULL, (directionChangePositions.back().y + world->TILE_SIZE) - getPosition().y);
			currentTrailObj.translate(NULL, getPosition().y);
		}
		else {
			currentTrailObj.resizeRect(NULL, getPosition().y - directionChangePositions.back().y);
		}

		if (direction.x < 0) {
			currentTrailObj.resizeRect((directionChangePositions.back().x + world->TILE_SIZE) - getPosition().x, NULL);
			currentTrailObj.translate(getPosition().x, NULL);
		}
		else {
			currentTrailObj.resizeRect(getPosition().x - directionChangePositions.back().x, NULL);
		}
	}
}

void Bike::draw(SDL_Renderer* renderer)
{
	currentTrailObj.draw(renderer);
	Entity::draw(renderer);
}

void Bike::onCollision(Entity* collidedWith)
{
	// TODO: kill player 
	// Do I want to use a delegate here? Multiple things will need to happen --
	// lightwalls need to be cleared in world/PlayState
	SDL_Log("BIKE: Collision detected!");
}
