#include "AsteroidsManager.h"

#include "Collisions.h"

AsteroidsManager::AsteroidsManager(SDLGame* game) : GameObject(game), rotationPhysics_(5),
	astroImage_(game->getResources()->getImageTexture(Resources::Astroid)), numAsteroids(0) {
}

AsteroidsManager::~AsteroidsManager() {
}

vector<Asteroid*>& AsteroidsManager::getAsteroids() {
	return asteroids_;
}

void AsteroidsManager::handleInput(Uint32 time, const SDL_Event& event) {
}

void AsteroidsManager::update(Uint32 time) {
	for (Asteroid* a : asteroids_)
		if (a->isActive()) {
			a->update(time);
		}
}

void AsteroidsManager::render(Uint32 time) {
	for (Asteroid* a : asteroids_)
		if (a->isActive()) {
			a->render(time);
		}
}

void AsteroidsManager::receive(Message* msg) {
	switch (msg->mType_) {
	case ASTEROID_INFO:
		initAsteroid(static_cast<PlayerInfoMsg*>(msg)->clientId_);
		break;
	case GAME_START:
		startGame();
		break;
	case ASTEROID_STATE:
		updateAsteroidState(static_cast<AsteroidStateMsg*>(msg));
		break;
	}
}

Asteroid * AsteroidsManager::getAsteroidDead()
{
	// recorre la lista de asteroides buscando uno inactivo
	// si lo encuentra, lo devuelve para reutilizarlo
	// si no, crea uno con los componentes del asteroids
	vector<Asteroid*>::iterator it;
	it = asteroids_.begin();
	while (it != asteroids_.end() && (*it)->isActive()) it++;

	if (it == asteroids_.end()) {
		asteroids_.push_back(new Asteroid(game_));
		asteroids_.back()->addPhysicsComponent(&circularPhysics_);
		asteroids_.back()->addRenderComponent(&astroImage_);
		asteroids_.back()->addPhysicsComponent(&rotationPhysics_);
		asteroids_.back()->setActive(false);
		return asteroids_.back();
	}
	else
		return (*it);
}

void AsteroidsManager::addAsteroid()
{
	Vector2D vel((1 - 2 * (rand() % 2))*((rand() % 10) + 1), ((rand() % 10) + 1));
	vel.normalize();
	vel = vel * 0.5;
	Vector2D pos(rand() % getGame()->getWindowWidth(), rand() % 30);
	Vector2D dir(0, -1);
	int width = (rand() % 10) + 20;
	int height = (rand() % 10) + 20;

	Asteroid* aux = getAsteroidDead();
	aux->setDirection(dir);
	aux->setPosition(pos);
	aux->setVelocity(vel);
	aux->setHeight(height);
	aux->setWidth(width);
	aux->setActive(true);
	numAsteroids++;
}

void AsteroidsManager::sendAsteroidsState()
{
	Asteroid* a = asteroids_[numAsteroids - 1];
	AsteroidStateMsg msg = { //
		(Uint8)numAsteroids,
		a->getPosition(), //
		a->getDirection(), //
		a->getVelocity(), //
		a->getWidth(), //
		a->getHeight() //
	};
	send(&msg);
}

////////////////TEMP

void AsteroidsManager::startGame()
{
	addAsteroid();
	sendAsteroidsState();
}

void AsteroidsManager::initAsteroid(Uint8 id)
{
}

void AsteroidsManager::updateAsteroidState(AsteroidStateMsg * msg)
{
	Asteroid* a = asteroids_[msg->Id_];

	if (a == nullptr) {
		a = getAsteroidDead();
	}
	a->setWidth(msg->width_);
	a->setHeight(msg->height_);
	a->setPosition(msg->pos_);
	a->setDirection(msg->dir_);
	a->setVelocity(msg->vel_);
}

