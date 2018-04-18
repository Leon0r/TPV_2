#include "CollisionManager.h"



CollisionManager::CollisionManager(SDLGame* game, AsteroidsManager* asteroidMngr, BulletsManager* bulletMngr, FightersManager* figterMngr, Bonus* bonus) :
	GameObject(game), bulletsManager_(bulletMngr), asteroidsManager_(asteroidMngr), fightersManager_(figterMngr), bonus_(bonus)
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
	if (fighter->isActive()) {
		for (Asteroid* a : asteroids) {
			if (a->isActive() && Collisions::collidesWithRotation(fighter, a)) {
				msg = new AstroidFighterCollision(a, fighter);
				send(msg);
				delete msg;
				msg = nullptr;
			}
		}
	}

	vector<Asteroid*>::iterator it;
	// bullets with asteroids
	// por cada bala mira si ha chocado con los asteroides solo si estan activos ambos
	// chequea balas sobre asteroides para que no cuente colisiones de balas 2 veces
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

	// Bullet with bonus
	if (bonus_->isActive())
		for (Bullet* bull : bullets) {
			if (bull->isActive() && Collisions::collidesWithRotation(bull, bonus_)) {
				msg = new BulletBonusCollision(bull);
				send(msg);
				delete msg;
				msg = nullptr;
			}
		}
}
