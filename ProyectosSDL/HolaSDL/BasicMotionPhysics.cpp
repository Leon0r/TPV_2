#include "BasicMotionPhysics.h"

BasicMotionPhysics::BasicMotionPhysics() {

}

BasicMotionPhysics::~BasicMotionPhysics() {
}

void BasicMotionPhysics::update(GameObject* o, Uint32 time) {
	Vector2D deltaMov (o->getVelocity().getX() * o->getDirection().getX(),
		o->getVelocity().getY() * o->getDirection().getY());
	/*deltaMov.setX(o->getVelocity().getX() * o->getDirection().getX());
	deltaMov.setY(o->getVelocity().getY() * o->getDirection().getY());*/

	o->setPosition(o->getPosition() + deltaMov);
}