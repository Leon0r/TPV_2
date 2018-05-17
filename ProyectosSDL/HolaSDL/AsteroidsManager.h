#pragma once

#include "GameObject.h"
#include "ImageRenderer.h"
#include "CircularMotionPhysics.h"
#include "RotationPhysics.h"
#include "Observer.h"
#include "SkeletonRenderer.h"
#include "Observable.h"
#include "Asteroid.h"

/*
 *
 */
class AsteroidsManager: 
	public GameObject, public Observer, public Observable 
{

public:
	AsteroidsManager(SDLGame* game);
	virtual ~AsteroidsManager();
	virtual vector<Asteroid*>& getAsteroids();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void receive(Message* msg);

private:

	int numAsteroids;
	// devuelve el 1º asteroide no activo si hay, 
	// si  no, crea uno y lo añade a asteroids_
	Asteroid * getAsteroidDead();
	// Añade un asteroide al juego
	virtual void addAsteroid();

	virtual void sendAsteroidsState();

	vector<Asteroid*> asteroids_;

	ImageRenderer astroImage_; // imagen del asteroide
	CircularMotionPhysics circularPhysics_; // movimiento toroidal
	RotationPhysics rotationPhysics_; // rotar asteroide todo el rato

	//TEMP
	virtual void startGame();
	virtual void initAsteroid(Uint8 id);
	virtual void updateAsteroidState(AsteroidStateMsg* msg);

};

