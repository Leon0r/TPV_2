#pragma once
#include "RenderComponent.h"
class LifeRenderer :
	public RenderComponent
{
public:
	LifeRenderer();
	virtual ~LifeRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

