#pragma once
#include "PhysicsComponent.h"

const int VEL_ROT = 200;
class RotationPhysics :
	public PhysicsComponent
{
public:
	RotationPhysics(int velRot = VEL_ROT);
	virtual ~RotationPhysics();
	virtual void update(GameObject* o, Uint32 time);

private:
	double angle = 0.0;
	int velRot_;
	Uint32 t = 0;
};

