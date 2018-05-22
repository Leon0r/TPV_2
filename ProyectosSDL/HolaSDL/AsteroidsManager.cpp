#include "AsteroidsManager.h"

#include "Collisions.h"

AsteroidsManager::AsteroidsManager(SDLGame* game) :
	GameObject(game), 
	asteroidRenderer_(game->getResources()->getImageTexture(Resources::Astroid)),
	rotationPhysics_(5)
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
		cout << "juego iniciado ";
		startGame();
		// add you code
		break;
		//add other cases
	}
}

void AsteroidsManager::startGame()
{
	if(game_->isMasterClient())
		addAsteroid();
}

Asteroid * AsteroidsManager::getAsteroidDead()
{
	if (asteroids_.size() <= numAsteroids) {
		asteroids_.resize(numAsteroids + 1);
	}

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
		a->setWidth(10);
		a->setHeight(10);
		// the id of the asteroid is its position in the vector
		a->setAsteroidId(numAsteroids);

		numAsteroids++;
		asteroids_.push_back(a);
	}
	cout << " " << a << endl;
	return a;
}

void AsteroidsManager::disableAsteroids()
{
	for (Asteroid* a : asteroids_) {
		a->setActive(false);
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
	cout << " " << a << endl;
	a->setPosition(pos);
	a->setVelocity(vel);
	a->setDirection(dir);
	a->setActive(true);
}

