#pragma once
#include "RenderComponent.h"
class BadgeRenderer :
	public RenderComponent
{
protected:
	int badge_ = 0;

public:
	BadgeRenderer();
	virtual ~BadgeRenderer();
	virtual void render(GameObject* o, Uint32 time);

	void setBadge(int badge) { badge_ = badge;}
};

