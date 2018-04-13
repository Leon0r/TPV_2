#pragma once
#include "Container.h"
class Bullet :
	public Container
{
public:
	Bullet(SDLGame* game);
	virtual ~Bullet();
	void setFighterID(int id) { fighterID_ = id; }
	int getFighterID() { return fighterID_; }

private:
	int fighterID_;
};

