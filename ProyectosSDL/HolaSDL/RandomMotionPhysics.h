#pragma once
#include "PhysicsComponent.h"
class RandomMotionPhysics :
	public PhysicsComponent
{
public:
	RandomMotionPhysics(Uint32 timeLapse = 0);
	virtual ~RandomMotionPhysics();

	virtual void update(GameObject* o, Uint32 time);

private:
	Uint32 timeLapse_, timeLastMov_;

};

