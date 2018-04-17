#include "BaseGunInputComponent.h"



BaseGunInputComponent::BaseGunInputComponent(SDL_Keycode trigger, int bullets, Uint32 timeInterval):
	bullets_(bullets), timeInterval_(timeInterval), trigger_(trigger), bulletsShoot(0)
{
}


BaseGunInputComponent::~BaseGunInputComponent()
{
}

void BaseGunInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == trigger_) {

 			if (timeTriggered_ + timeInterval_ < time) // si se ha pasado el intervalo
				bulletsShoot = 0; // reinicia balas disparadas

			if (bulletsShoot == 0)
				timeTriggered_ = SDL_GetTicks(); // coge el momento del primer disparo

			if (bulletsShoot < bullets_) { // si las balas disparadas es menor que las permitidas
				bulletsShoot++;
				shoot(o);
			}
		}
	}
}
