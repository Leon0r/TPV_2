#pragma once
#include <time.h>
#include "GameObject.h"
#include "Observer.h"
#include "Observable.h"
#include "ImageRenderer.h"
#include "CircularMotionPhysics.h"
#include "RotationPhysics.h"

const int MARGEN = 10; // distancia maxima a los bordes de pantalla
const int VEL_MAX = 100;

class AsteroidsManager :
	public GameObject, public Observer, public Observable
{
public:
	AsteroidsManager(SDLGame* game);
	virtual ~AsteroidsManager();

	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual vector<Asteroid*>& getAsteroids() { return asteroids_; };
	virtual void receive(Message* msg);

private:
	// devuelve el 1º asteroide no activo si hay, 
	// si  no, crea uno y lo añade a asteroids_
	Asteroid* getAsteroidDead();
	// pone todos los asteroides a noActivo 
	// y crea los asteroides iniciales del juego
	void initAsteroids();
	void asteroidToLaterals(Asteroid* asteroid);
	void asteroidCollision(Asteroid* asteroid);

	vector<Asteroid*> asteroids_;
	ImageRenderer astroImage_; // imagen del asteroide
	CircularMotionPhysics circularPhysics_; // movimiento toroidal
	RotationPhysics rotationPhysics_; // rotar asteroide todo el rato

	int numOfAsteroids_; // numero de asteroides activos
};

