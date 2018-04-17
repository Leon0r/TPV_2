#ifndef CIRCULARMOTIONPHYSICS_H_
#define CIRCULARMOTIONPHYSICS_H_

#include "PhysicsComponent.h"
class CircularMotionPhysics :
	public PhysicsComponent
{
	// movimiento toroidal
public:
	CircularMotionPhysics();
	virtual ~CircularMotionPhysics();

	virtual void update(GameObject* o, Uint32 time);
};
#endif /* CIRCULARMOTIONPHYSICS_H_ */