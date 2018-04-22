#pragma once
#include "BaseGunInputComponent.h"
class MultibulletGunInputComponent :
	public BaseGunInputComponent
{
public:
	MultibulletGunInputComponent(SDL_Keycode trigger, int bullets, Uint32 timeInterval, bool superBullet = false);
	virtual ~MultibulletGunInputComponent();
	virtual void shoot(GameObject* o);
};

