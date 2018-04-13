#include "FightersManager.h"



FightersManager::FightersManager(SDLGame* game, Observer* bulletsManager) :GameObject(game),
renderComp_(ImageRenderer(game->getResources()->getImageTexture(Resources::Airplanes), { 4,3 }, { 3,2 })),
fighter_(Fighter(game, 0)), accelerationComp_(SDLK_w, SDLK_s, 0.9, 5.0, 0.9), rotationComp_(SDLK_e, SDLK_q),
gunComp1_(GunInputComponent(SDLK_SPACE,5,300)), gunComp2_(GunInputComponent(SDLK_SPACE, 3000, 1))
{
	gunComp1_.registerObserver(bulletsManager);
	gunComp2_.registerObserver(bulletsManager);

	fighter_.setPosition({ (double)(game_->getWindowWidth() / 2), (double)(game_->getWindowHeight() / 2) });
	fighter_.setHeight(50.0);
	fighter_.setWidth(50.0);
	fighter_.addPhysicsComponent(&circularPhysics_);
	fighter_.addInputComponent(&accelerationComp_);
	fighter_.addInputComponent(&rotationComp_);
	fighter_.addInputComponent(&gunComp1_);

	fighter_.setActive(false);
	fighter_.addRenderComponent(&renderComp_);
}


FightersManager::~FightersManager()
{
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
	case BADGE_ON:
		badgeOn();
		break;
	case BADGE_OFF:
		badgeOff();
		break;
	}
}

void FightersManager::badgeOn()
{
	//// quitar arma 1 y poner la 2
	fighter_.delInputComponent(&gunComp1_);
	fighter_.addInputComponent(&gunComp2_);
	fighter_.addRenderComponent(&badgeRender_);
}

void FightersManager::badgeOff()
{
	// quitar arma 1 y poner la 2
	fighter_.delInputComponent(&gunComp2_);
	fighter_.addInputComponent(&gunComp1_);
	fighter_.delRenderComponent(&badgeRender_);
}
