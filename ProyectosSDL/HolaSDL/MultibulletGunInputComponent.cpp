#include "MultibulletGunInputComponent.h"
#include <algorithm> 


MultibulletGunInputComponent::MultibulletGunInputComponent(SDL_Keycode trigger, int bullets, Uint32 timeInterval, bool superBullet):BaseGunInputComponent(trigger, bullets, timeInterval, superBullet)
{
}


MultibulletGunInputComponent::~MultibulletGunInputComponent()
{
}

void MultibulletGunInputComponent::shoot(GameObject * o)
{
	for (int i = 0; i < 6; i++) {
		Vector2D pos = o->getPosition();
		Vector2D a = { o->getWidth() / 2, o->getHeight() / 2 };
		pos = pos + a;
		pos = pos + (o->getDirection()*o->getHeight() / 2);

		double mgn = max((o->getVelocity().magnitude()*velBullet), 2.0); // velocidad calculada a partir de la vel del fighter para que no se choque con su propia bala
		Vector2D velB = o->getDirection()*mgn;
		velB.rotate(60 * i);

		FighterIsShooting msg(static_cast<Fighter*>(o), pos, velB, superBullet_);
		send(&msg);
	}
}
