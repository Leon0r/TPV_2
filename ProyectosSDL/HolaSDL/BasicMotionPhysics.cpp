#include "BasicMotionPhysics.h"



BasicMotionPhysics::BasicMotionPhysics()
{
}


BasicMotionPhysics::~BasicMotionPhysics()
{
}

void BasicMotionPhysics::update(GameObject * o, Uint32 time)
{
	Vector2D nPos = { o->getPosition().getX() + o->getVelocity().getX(),o->getPosition().getY() - o->getVelocity().getY() };
	o->setPosition(nPos);
}
