#pragma once
#include "PhysicsComponent.h"
class BasicMotionPhysics :
	public PhysicsComponent
{
	// movimiento basico hacia delante
public:
	BasicMotionPhysics();
	virtual ~BasicMotionPhysics();
	virtual void update(GameObject* o, Uint32 time);
};

