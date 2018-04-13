#include "BaseGunInputComponent.h"



BaseGunInputComponent::BaseGunInputComponent(SDL_Keycode trigger, int bullets, Uint32 timeWaiting):
	bullets_(bullets), timeWaiting_(timeWaiting), trigger_(trigger), bulletsShoot(0)
{
}


BaseGunInputComponent::~BaseGunInputComponent()
{
}

void BaseGunInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == trigger_ &&
			(timeTriggered_ + timeWaiting_) <= time) {
			shoot(o);
		}
	}
}
