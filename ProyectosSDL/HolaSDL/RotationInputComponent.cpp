#include "RotationInputComponent.h"
#include <iostream>


RotationInputComponent::RotationInputComponent(SDL_Keycode clock, SDL_Keycode counterClock):
	clock_(clock), counterClock_(counterClock)
{
}


RotationInputComponent::~RotationInputComponent()
{
}

void RotationInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	Vector2D dir = o->getDirection();

	if (event.type == SDL_KEYDOWN) {
		std::cout << o->getDirection() << std::endl;
		if (event.key.keysym.sym == clock_) {
			dir.rotate(-angle);
			o->setDirection(dir);
		}
		else if (event.key.keysym.sym == counterClock_) {
			dir.rotate(angle);
			o->setDirection(dir);
		}
	}
}
