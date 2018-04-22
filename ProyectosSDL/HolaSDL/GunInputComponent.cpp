#include "GunInputComponent.h"
#include <algorithm>  


GunInputComponent::GunInputComponent(SDL_Keycode trigger, int bullets, Uint32 timeWaiting):
BaseGunInputComponent(trigger, bullets, timeWaiting)
{
}


GunInputComponent::~GunInputComponent()
{
}

// crea la bala disparada
void GunInputComponent::shoot(GameObject* o)
{
	Vector2D pos = o->getPosition();
	Vector2D a = { o->getWidth() / 2, o->getHeight() / 2 };
	pos = pos + a;
	pos = pos + (o->getDirection()*o->getHeight() / 2);

	double mgn = max((o->getVelocity().magnitude()*velBullet), 2.0); // velocidad calculada a partir de la vel del fighter para que no se choque con su propia bala
	Vector2D velB = o->getDirection()*mgn;

	FighterIsShooting msg(static_cast<Fighter*>(o), pos, velB, superBullet_);
	send(&msg);
}
