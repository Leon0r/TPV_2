#pragma once
#include "RenderComponent.h"
class BadgeRenderer :
	public RenderComponent
{
public:
	BadgeRenderer();
	virtual ~BadgeRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

