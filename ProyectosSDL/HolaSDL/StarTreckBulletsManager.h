#pragma once
#include "GameObject.h"
#include "BulletsManager.h"
#include "BasicMotionPhysics.h"
#include "FillRectRenderer.h"

class StarTreckBulletsManager :
	public GameObject, public BulletsManager
{
public:
	StarTreckBulletsManager(SDLGame* game);
	virtual ~StarTreckBulletsManager();

	virtual void handleInput(Uint32 time, const SDL_Event&) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual vector<Bullet*>& getBullets() { return bullets_; };

private:
	Bullet * getBulletDead();
	virtual void receive(Message* msg);
	virtual void shoot(Fighter* owner, Vector2D pos, Vector2D vel);
	virtual void deactivateBullets(); // desactiva todas las balas
	virtual bool isOutOfBounds(Bullet* b);
	
	FillRectRenderer bulletRenderer_; // renderer de las balas
	BasicMotionPhysics bulletPhysics_; // movimiento de las balas
};

