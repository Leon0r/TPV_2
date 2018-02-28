#include "AccelerationInputComponent.h"



AccelerationInputComponent::AccelerationInputComponent(SDL_Keycode speedUp, SDL_Keycode speedDown):speedDown_(speedDown), speedUp_(speedUp)
{
}


AccelerationInputComponent::~AccelerationInputComponent()
{
}

void AccelerationInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {
	Vector2D velocity = o->getVelocity();

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == speedUp_) {
			//velocity = velocity + {1, 1};
		}
		else if (event.key.keysym.sym == speedDown_) {
			velocity.set(1, 0);
		}
	}

	o->setVelocity(velocity);
}