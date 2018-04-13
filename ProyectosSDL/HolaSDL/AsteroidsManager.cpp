#include "AsteroidsManager.h"



AsteroidsManager::AsteroidsManager(SDLGame* game):GameObject(game),
astroImage_ (ImageRenderer(game->getResources()->getImageTexture(Resources::Astroid)))
{
	numOfAsteroids_ = 0;
}


AsteroidsManager::~AsteroidsManager()
{
}

void AsteroidsManager::update(Uint32 time)
{
	for (Asteroid* a : asteroids_)
		if (a->isActive())
			a->update(time);
}

void AsteroidsManager::render(Uint32 time)
{
	for (Asteroid* a : asteroids_)
		if (a->isActive())
			a->render(time);
}

void AsteroidsManager::receive(Message * msg)
{
	switch (msg->id_) {
	case BULLET_ASTROID_COLLISION: {
		BulletAstroidCollision * a = static_cast<BulletAstroidCollision*>(msg);
		asteroidCollision(a->astroid_);
		break; 
	}
	case ROUND_START:
		initAsteroids();
		break;
	}
}

// Busca el primer asteroide inactivo o crea uno nuevo al final
Asteroid * AsteroidsManager::getAsteroidDead()
{
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

void AsteroidsManager::initAsteroids()
{
	srand(time(NULL));
	for (Asteroid* a : asteroids_)
		a->setActive(false);

	int numAst = rand() % 6 + 5;
	numOfAsteroids_ = numAst; // el num de asteroides activos es numAst
	Asteroid* aux;
	
	for (int i = 0; i < numAst; i++) {
		aux = getAsteroidDead(); // busca el primer asteroide desactivado
		if (aux != nullptr) {
			aux->setGenerations(rand() % 3 + 1); // generacion entre 2 y 4 incluidos
			aux->setWidth(12+aux->getGenerations() * 10);
			aux->setHeight(12+aux->getGenerations() * 10);
			asteroidToLaterals(aux); // Lo inicializa en uno de los laterales
		}
	}
}

// Inicializa el asteroide en uno de los laterales con vel aleatoria 
void AsteroidsManager::asteroidToLaterals(Asteroid * asteroid)
{
	// 0 arriba, 1 abajo, 2 izqu, 3 dcha
	int lateral = rand() % 4;
	double auxX, auxY;
	double auxVelX, auxVelY;

	if (asteroid != nullptr) {
		asteroid->toggleActive(); // lo activa
		// laterales superior e inferior (0,1)
		if (lateral <= 1) {
			auxX = rand() % game_->getWindowWidth();
			auxY = rand() % MARGEN;
			if (lateral == 0)
				auxY = game_->getWindowHeight() - auxY;
		}
		else {
			auxY = rand() % game_->getWindowHeight();
			auxX = rand() % MARGEN;
			if (lateral == 3)
				auxX = game_->getWindowWidth() - auxX;
		}

		// velocidad aleatoria
		auxVelX = (double)(rand() % VEL_MAX + 1)/100;
		auxVelY = (double)(rand() % VEL_MAX + 1)/100;

		Vector2D vel = { auxVelX, auxVelY };
		int angleRnd = rand() % 360;
		vel.rotate(angleRnd);

		asteroid->setPosition({ auxX, auxY });
		asteroid->setVelocity(vel);
		asteroid->setDirection(vel);
	}
}

void AsteroidsManager::asteroidCollision(Asteroid * asteroid)
{
	asteroid->toggleActive(); // lo pone a inactivo
	numOfAsteroids_--;

	if (asteroid->getGenerations() > 1) {
		Vector2D vel, pos;
		int nextGen = asteroid->getGenerations() - 1;
		int babyAst = rand() % 3 + 2;
		Asteroid* a;
		numOfAsteroids_ += babyAst;

		for (int i = 0; i < babyAst; i++) {
			vel = asteroid->getVelocity();
			vel.rotate(i * 30);
			pos = asteroid->getPosition() + vel;

			a = getAsteroidDead();
			a->setActive(true);
			a->setGenerations(nextGen);
			a->setWidth(12 + a->getGenerations() * 10);
			a->setHeight(12 + a->getGenerations() * 10);
			a->setDirection(vel);
			a->setVelocity(vel);
			a->setPosition(pos);
		}
	}

	if (numOfAsteroids_ <= 0)
		send(&Message(NO_MORE_ATROIDS));
}
