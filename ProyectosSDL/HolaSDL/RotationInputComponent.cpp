#include "RotationInputComponent.h"

RotationInputComponent::~RotationInputComponent()
{
}

void RotationInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	Vector2D dir = o->getDirection();

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == Clock) {
			dir.rotate(angle);
			o->setDirection(dir);
		}
		else if(event.key.keysym.sym == CounterClock){
			dir.rotate(-angle);
			o->setDirection(dir);
		}
	}
}
