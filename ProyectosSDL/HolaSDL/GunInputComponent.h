#pragma once
#include"BaseGunInputComponent.h"

class GunInputComponent :
	public BaseGunInputComponent // base de gunInput para que sea extensible a otros tipos de armas
{
public:
	GunInputComponent(SDL_Keycode trigger, int bullets, Uint32 timeWaiting);
	virtual ~GunInputComponent();
	virtual void shoot(GameObject* o);
};

