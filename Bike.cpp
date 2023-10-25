#include "Bike.h"
#include "Lightwall.h"
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

	velocity = { 0, 0 };
	trailSegments = {};
	directionChangePositions = {};
}

Bike::Bike(int startX, int startY, int w, int h, int moveSpeed, SDL_Color color)
	:Bike(startX, startY, w, h, moveSpeed)
{
	this->color = color;
}

bool Bike::changeVelocity(Velocity newVelocity)
{
	SDL_Rect newLightwallRect = {};

	// Can only change y-movement if we are not already moving in the y-direction
	// Otherwise it would be very easy to accidentally collide into yourself
	if (velocity.y == 0 && newVelocity.y != 0) {
		velocity.y = newVelocity.y;
		velocity.x = newVelocity.x;
	// Can only change x-movement if we are not already moving in the x-direction
	} else if (velocity.x == 0 && newVelocity.x != 0) {
		velocity.x = newVelocity.x;
		velocity.y = newVelocity.y;
	}
	else {
		return false;
	}
	
	trailSegments.push_back(currentTrailObj);

	newLightwallRect.w = 16;
	newLightwallRect.h = 16;
	newLightwallRect.x = getPosition().x;
	newLightwallRect.y = getPosition().y;
	
	directionChangePositions.push_back(getPosition());
	currentTrailObj = Lightwall(newLightwallRect);

	return true;
;}

void Bike::update(float deltaTime)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_W]) {
		changeVelocity(UP);
	}

	if (currentKeyStates[SDL_SCANCODE_S]) {
		changeVelocity(DOWN);
	}

	if (currentKeyStates[SDL_SCANCODE_A]) {
		changeVelocity(LEFT);
	}

	if (currentKeyStates[SDL_SCANCODE_D]) {
		changeVelocity(RIGHT);
	}

	int newX = getPosition().x + (int)(velocity.x * deltaTime * moveSpeed);
	int newY = getPosition().y + (int)(velocity.y * deltaTime * moveSpeed);
	translate(newX, newY);

	if (directionChangePositions.size() != 0) {
		if (velocity.y < 0) {
			currentTrailObj.resizeRect(NULL, (directionChangePositions.back().y + 16.0f) - getPosition().y);
			currentTrailObj.translate(NULL, getPosition().y);
		}
		else {
			currentTrailObj.resizeRect(NULL, getPosition().y - directionChangePositions.back().y);
		}

		if (velocity.x < 0) {
			currentTrailObj.resizeRect((directionChangePositions.back().x + 16.0f) - getPosition().x, NULL);
			currentTrailObj.translate(getPosition().x, NULL);
		}
		else {
			currentTrailObj.resizeRect(getPosition().x - directionChangePositions.back().x, NULL);
		}
	}
}

void Bike::draw(SDL_Renderer* renderer)
{
	// Draw order: Draw trail, the current segment, and then head (or bike) on top
	if (trailSegments.size() != 0) {
		for (auto& segment : trailSegments) {
			segment.draw(renderer);
		}
	}
	currentTrailObj.draw(renderer);
	Entity::draw(renderer);
}