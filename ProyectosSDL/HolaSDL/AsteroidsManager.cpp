#include "AsteroidsManager.h"
#include "Collisions.h"

AsteroidsManager::AsteroidsManager(SDLGame* game) :
	GameObject(game), 
	asteroidRenderer_(game->getResources()->getImageTexture(Resources::Astroid)),
	rotationPhysics_(5), skeletonRendered_()
{

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
	// timer de creacion de asteroides
	Uint32 timeNow = SDL_GetTicks();
	if (timeLast + timerNewAst <= timeNow && game_->isMasterClient() && running) {
		addAsteroid();
		timeLast = SDL_GetTicks();
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
	case GAME_START:
		startGame(); // añade 4 asteroides
		break;
	case ASTEROID_STATE:
		if (!game_->isMasterClient()) {
			AsteroidStateMsg* m = static_cast<AsteroidStateMsg*>(msg);
			addAsteroid(m->Id_, m->pos_, m->dir_, m->vel_, m->width_, m->height_);
		}
		break;
	case DISABLE_ASTEROID:
		if (!game_->isMasterClient()) {
			disableAsteroidMsg* m = static_cast<disableAsteroidMsg*>(msg);
			disableAsteroid(m->Id_);
		}
		break;
	case GAME_WAIT:
	case GAME_OVER:
		running = false;
		disableAsteroids();
		break;
	}
}

void AsteroidsManager::startGame()
{
	if (game_->isMasterClient()) {
		for (int i = 0; i < 4; i++)
			addAsteroid();
		running = true;
	}
}

Asteroid * AsteroidsManager::getAsteroidDead()
{
	// look for an inactive asteroid
	vector<Asteroid*>::iterator it = asteroids_.begin();
	while (it != asteroids_.end() && *it != nullptr
		&& (*it)->isActive())
		it++;

	Asteroid* a = nullptr;
	if (it != asteroids_.end() && *it != nullptr) {
		a = *it;
	}
	else { // if no inactive asteroid, create one;
		a = new Asteroid(getGame());
		a->addPhysicsComponent(&basicMotion_);
		a->addPhysicsComponent(&deactiveteOnBorder_);
		a->addPhysicsComponent(&rotationPhysics_);
		a->addRenderComponent(&asteroidRenderer_);
		a->addRenderComponent(&skeletonRendered_);
		a->setWidth(10);
		a->setHeight(10);
		// the id of the asteroid is its position in the vector
		a->setAsteroidId(numAsteroids);
		asteroids_.push_back(a);
	}
	return a;
}

void AsteroidsManager::disableAsteroids()
{
	if (game_->isMasterClient())
		for (Asteroid* a : asteroids_) {
			a->setActive(false);
			disableAsteroidMsg msg = { a->getAsteroidId() };
			send(&msg);
		}
}

void AsteroidsManager::disableAsteroid(Uint8 id)
{
	asteroids_[id]->setActive(false);
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

	Asteroid* a = getAsteroidDead();

	a->setPosition(pos);
	a->setVelocity(vel);
	a->setDirection(dir);
	a->setHeight(height);
	a->setWidth(width);
	a->setActive(true);

	numAsteroids++;
	

	AsteroidStateMsg msg = { a->getAsteroidId(), a->getPosition(), a->getDirection(), 
		a->getVelocity(), a->getWidth(), a->getHeight()};
	send(&msg);
}

void AsteroidsManager::addAsteroid(Uint8 Id, Vector2D pos, Vector2D dir, 
	Vector2D vel, double width, double height)
{
	Asteroid* a = getAsteroidDead();
	a->setAsteroidId(Id);
	a->setPosition(pos);
	a->setDirection(dir);
	a->setVelocity(vel);
	a->setWidth(width);
	a->setHeight(height);
	a->setActive(true);
	numAsteroids++;
}

