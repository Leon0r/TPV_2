#pragma once
#include "InputComponent.h"
#include "Observable.h"

const double velBullet = 2.0;
class BaseGunInputComponent :
	public InputComponent, public Observable
{
public:
	BaseGunInputComponent(SDL_Keycode trigger, int bullets, Uint32 timeInterval);
	virtual ~BaseGunInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
	virtual void shoot(GameObject* o) {};

protected:
	SDL_Keycode trigger_;
	int bullets_, bulletsShoot;
	Uint32 timeInterval_, timeTriggered_;
};

