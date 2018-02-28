#include "ToroidalMotionPhysics.h"



ToroidalMotionPhysics::ToroidalMotionPhysics()
{
}


ToroidalMotionPhysics::~ToroidalMotionPhysics()
{
}

void ToroidalMotionPhysics::update(GameObject* o, Uint32 time)
{
	Vector2D position;

	position = o->getPosition() + o->getVelocity();

	if (position.getX() < 0)
		position.setX(o->getGame()->getWindowWidth());
	else if(position.getX() > (o->getGame()->getWindowWidth()))
		position.setX(0);

	if (position.getY() < 0)
		position.setY(o->getGame()->getWindowHeight());
	else if (position.getY() > o->getGame()->getWindowHeight())
		position.setY(0);

	o->setPosition(position);
}
