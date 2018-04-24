#pragma once
#include "GameObject.h"
#include "Observer.h"
#include "ImageRenderer.h"
#include "CircularMotionPhysics.h"
#include "AccelerationInputComponent.h"
#include "RotationInputComponent.h"
#include "GunInputComponent.h"
#include "MultibulletGunInputComponent.h"
#include "BadgeRenderer.h"

class FightersManager :
	public GameObject, public Observer
{
public:
	FightersManager(SDLGame* game, Observer* bulletsManager);
	virtual ~FightersManager();

	virtual void handleInput(Uint32 time, const SDL_Event& event) { if (fighter_.isActive()) 
		fighter_.handleInput(time, event); }
	virtual void update(Uint32 time) { if (fighter_.isActive()) fighter_.update(time); }
	virtual void render(Uint32 time) { if (fighter_.isActive()) fighter_.render(time); }

	Fighter* getFighter() { return &fighter_; }
	virtual void receive(Message* msg);

private:
	virtual void badgeOn();
	virtual void badgeOff();
	Fighter fighter_;
	CircularMotionPhysics circularPhysics_; // movimiento toroidal
	AccelerationInputComponent accelerationComp_; // para acelerar
	ImageRenderer renderComp_; // imagen, sprite de a nave
	RotationInputComponent rotationComp_; // para girar la nave con las teclas
	vector<BaseGunInputComponent*> guns_; // armas del fighter

	//BaseGunInputComponent* gunComp1_; // 5 balas cada 3 segundos
	//BaseGunInputComponent* gunComp2_; // 10 segs de balas ilimitadas
	//BaseGunInputComponent* gunComp3_; // multibullets

	BadgeRenderer badgeRender_; // renderer de la insignia del super arma
};

