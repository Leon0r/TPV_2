#pragma once
#include "PhysicsComponent.h"
class ToroidalMotionPhysics :
	public PhysicsComponent
{
public:
	ToroidalMotionPhysics();
	virtual ~ToroidalMotionPhysics();

	virtual void update(GameObject* o, Uint32 time);
};

