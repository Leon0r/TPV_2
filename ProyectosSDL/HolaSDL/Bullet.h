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
	bool isIndestructible() { return indestructible; }
	void setIndestructible(bool indstruct) { indestructible = indstruct; }
private:
	int fighterID_;
	bool indestructible = false; // si se destruye al chocar con el primer asteroide o no
};

