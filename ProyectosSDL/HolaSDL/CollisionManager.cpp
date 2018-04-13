#include "CollisionManager.h"



CollisionManager::CollisionManager(SDLGame* game, AsteroidsManager* asteroidMngr, BulletsManager* bulletMngr, FightersManager* figterMngr) :
	GameObject(game), bulletsManager_(bulletMngr), asteroidsManager_(asteroidMngr), fightersManager_(figterMngr)
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::update(Uint32 time)
{
	vector<Bullet*> bullets = bulletsManager_->getBullets();
	vector<Asteroid*> asteroids = asteroidsManager_->getAsteroids();
	Fighter* fighter = fightersManager_->getFighter();

	Message* msg;

	// fighters with asteroids
	for (Asteroid* a : asteroids) {
		if (fighter->isActive() && a->isActive() && Collisions::collidesWithRotation(fighter, a)) {
			msg = new AstroidFighterCollision(a, fighter);
			send(msg);
			delete msg;
			msg = nullptr;
		}
	}

	vector<Asteroid*>::iterator it;
	// bullets with asteroids
	for (Bullet* bull : bullets) {
		if (bull->isActive()) {
			it = asteroids.begin();
			while (it != asteroids.end() && !Collisions::collidesWithRotation(bull, (*it)))
				it++;
			if (it != asteroids.end() && (*it)->isActive()) {
				msg = new BulletAstroidCollision(bull, (*it));
				send(msg);
				delete msg;
				msg = nullptr;
			}
		}
	}
}
