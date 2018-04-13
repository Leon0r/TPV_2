#include "BasicMotionPhysics.h"



BasicMotionPhysics::BasicMotionPhysics()
{
}


BasicMotionPhysics::~BasicMotionPhysics()
{
}

void BasicMotionPhysics::update(GameObject * o, Uint32 time)
{
	Vector2D nPos = o->getPosition() + o->getVelocity();
	o->setPosition(nPos);
}
