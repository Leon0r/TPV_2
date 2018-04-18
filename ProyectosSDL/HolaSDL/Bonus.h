#pragma once
#include "Container.h"
#include "Observer.h"
#include "ImageRenderer.h"
#include "RandomMotionPhysics.h"
#include "RotationPhysics.h"

class Bonus :
	public Container, public Observer
{
public:
	Bonus(SDLGame* game);
	virtual ~Bonus();

protected:
	virtual void receive(Message* msg);
};

