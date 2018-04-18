#include "RotationPhysics.h"



RotationPhysics::RotationPhysics(int velRot):velRot_(velRot)
{
}


RotationPhysics::~RotationPhysics()
{
}

void RotationPhysics::update(GameObject * o, Uint32 time)
{
	if (t + velRot_ < time) {
		t = SDL_GetTicks();
		angle++;

		if (angle == 360.0) 
			angle = 0.0;

		Vector2D aux = o->getDirection();
		int a = o->getDirection().angle({ 0,-1 });
		aux.rotate(a + angle);
		o->setDirection(aux);
	}
}
