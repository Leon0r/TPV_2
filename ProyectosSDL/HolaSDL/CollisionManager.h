#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "Collisions.h"
#include "BulletsManager.h"
#include "AsteroidsManager.h"
#include "FightersManager.h"
#include "Bonus.h"

class CollisionManager :
	public GameObject, public Observable
{
public:
	CollisionManager(SDLGame* game, AsteroidsManager* asteroidMngr, 
		BulletsManager* bulletMngr, FightersManager* figterMngr, Bonus* bonus);
	virtual ~CollisionManager();

	virtual void handleInput(Uint32 time, const SDL_Event&) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time) {};

private:
	BulletsManager* bulletsManager_;
	AsteroidsManager* asteroidsManager_;
	FightersManager* fightersManager_;
	Bonus* bonus_;
};

