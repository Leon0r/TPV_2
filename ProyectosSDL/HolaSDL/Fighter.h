#pragma once
#include "Container.h"
class Fighter :
	public Container
{
public:
	Fighter(SDLGame* game, int id);
	virtual ~Fighter();
	int getID() { return id_; }

	int getWeapon() { return weapon_; }
	void setWeapon(int gun) { weapon_ = gun; }

private:
	int id_;
	int weapon_ = 0;
};

