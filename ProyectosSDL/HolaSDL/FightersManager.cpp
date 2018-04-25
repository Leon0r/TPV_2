#include "FightersManager.h"



FightersManager::FightersManager(SDLGame* game, Observer* bulletsManager) :GameObject(game),
renderComp_(ImageRenderer(game->getResources()->getImageTexture(Resources::Airplanes), { 4,3 }, { 3,2 })),
fighter_(Fighter(game, 0)), accelerationComp_(SDLK_UP, SDLK_DOWN, 0.2, 5, 0.9), rotationComp_(SDLK_LEFT, SDLK_RIGHT)
{
	guns_.push_back(new GunInputComponent(SDLK_SPACE, 5, 3000)); // gun basica (5 balas cada 3 segs)
	guns_.push_back(new GunInputComponent(SDLK_SPACE, 5, 3000, true)); // igual que el anterior pero las balas no se destruyen al chocar con asteroides
	guns_.push_back(new GunInputComponent(SDLK_SPACE, 3000, 1)); // gun badge (balas infinitas durante 10 segs)
	guns_.push_back(new MultibulletGunInputComponent(SDLK_SPACE, 5, 3000)); // Dispara en estrella


	for (BaseGunInputComponent* gun : guns_)
		gun->registerObserver(bulletsManager);


	fighter_.setPosition({ (double)(game_->getWindowWidth() / 2), (double)(game_->getWindowHeight() / 2) });
	fighter_.setHeight(50.0);
	fighter_.setWidth(50.0);
	fighter_.addPhysicsComponent(&circularPhysics_);
	fighter_.addInputComponent(&accelerationComp_);
	fighter_.addInputComponent(&rotationComp_);
	fighter_.addInputComponent(guns_.front());
	fighter_.setWeapon(0);

	fighter_.setActive(false);

	fighter_.addRenderComponent(&renderComp_);
}


FightersManager::~FightersManager()
{
	for (BaseGunInputComponent* gun : guns_)
		delete gun;
}

void FightersManager::receive(Message * msg)
{
	switch (msg->id_) {
	case ROUND_START: {
		fighter_.setActive(true);
		fighter_.setPosition({ (double)(game_->getWindowWidth() / 2), (double)(game_->getWindowHeight() / 2) });
		fighter_.setVelocity({ 0.1,0.1 });
		break;
	}
	case ROUND_OVER: 
		fighter_.setActive(false);
		break; 
	case GAME_OVER:
		fighter_.setActive(false);
		break;
	case BADGE_ON: {
		BadgeIsOn* b = static_cast<BadgeIsOn*>(msg);
		badgeOn(b->badgeID_);
		break; }
	case BADGE_OFF:
		badgeOff();
		break;
	}
}

void FightersManager::badgeOn(int GunType)
{
	//// quitar todas las armas y poner la de tipo GunType
	if (GunType > 0 && GunType < guns_.size()) {
		for (BaseGunInputComponent* gun : guns_)
			fighter_.delInputComponent(gun);

		fighter_.addInputComponent(guns_[GunType]);
		badgeRender_.setBadge(GunType);
		fighter_.setWeapon(GunType);
		fighter_.addRenderComponent(&badgeRender_);
	}
}

void FightersManager::badgeOff()
{
	// quita todas las armas y pone la basica ([0])
	for (BaseGunInputComponent* gun : guns_)
		fighter_.delInputComponent(gun);

	fighter_.addInputComponent(guns_[0]);
	fighter_.delRenderComponent(&badgeRender_);
	fighter_.setWeapon(0);
}
