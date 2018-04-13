#include "GunInputComponent.h"
#include <algorithm>  


GunInputComponent::GunInputComponent(SDL_Keycode trigger, int bullets, Uint32 timeWaiting):
BaseGunInputComponent(trigger, bullets, timeWaiting)
{
}


GunInputComponent::~GunInputComponent()
{
}


void GunInputComponent::shoot(GameObject* o)
{
	Uint32 shot = SDL_GetTicks();
	timeTriggered_ = SDL_GetTicks();

	Vector2D pos = o->getPosition();
	Vector2D a = { o->getWidth() / 2, o->getHeight() / 2 };
	pos = pos + a;
	Vector2D b = { o->getDirection().getX()*o->getHeight() / 2, -o->getDirection().getY()*o->getHeight() / 2 };
	pos = pos + b;

	double mgn = max((o->getVelocity().magnitude()*velBullet), 2.0);
	Vector2D velB = o->getDirection()*mgn;

	Message * msg = new FighterIsShooting(static_cast<Fighter*>(o), pos, velB);
	send(msg);
	delete msg;
	msg = nullptr;

}
