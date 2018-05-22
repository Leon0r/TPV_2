#pragma once

#include "GameObject.h"
#include "ImageRenderer.h"
#include "CircularMotionPhysics.h"
#include "RotationPhysics.h"
#include "Observer.h"
#include "SkeletonRenderer.h"
#include "Observable.h"
#include "Asteroid.h"
#include "DeActivateOnBorderExit.h"

/*
 *
 */


class AsteroidsManager: public GameObject, public Observer, public Observable {

public:
	AsteroidsManager(SDLGame* game);
	virtual ~AsteroidsManager();
	virtual vector<Asteroid*>& getAsteroids();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

private:

	virtual void receive(Message* msg);
	virtual void startGame();
	virtual Asteroid* getAsteroidDead();
	virtual void disableAsteroids();
	virtual void disableAsteroid(Uint8 id);
	virtual void addAsteroid();
	virtual void addAsteroid(Uint8 Id, Vector2D pos, Vector2D dir, Vector2D vel, double width, double height);
	vector<Asteroid*> asteroids_;

	ImageRenderer asteroidRenderer_;
	SkeletonRendered skeletonRendered_;
	RotationPhysics rotationPhysics_;
	DeActivateOnBorderExit deactiveteOnBorder_;
	BasicMotionPhysics basicMotion_;

	int numAsteroids = 0;
	Uint32 timeLast = 0;
	Uint32  timerNewAst = 5000;
	bool running = false;

};

