#pragma once
#include"BaseGunInputComponent.h"

class GunInputComponent :
	public BaseGunInputComponent
{
public:
	GunInputComponent(SDL_Keycode trigger, int bullets, Uint32 timeWaiting);
	virtual ~GunInputComponent();
	virtual void shoot(GameObject* o);
};

