#include "RandomMotionPhysics.h"



RandomMotionPhysics::RandomMotionPhysics(Uint32 timeLapse):timeLapse_(timeLapse), timeLastMov_(0)
{
	
}


RandomMotionPhysics::~RandomMotionPhysics()
{
}

void RandomMotionPhysics::update(GameObject * o, Uint32 time)
{
	// Si ha pasado el tiempo, se mueve a una pos aleatoria
	if (timeLastMov_ + timeLapse_ < time) { 
		timeLastMov_ = SDL_GetTicks();
		double x = rand() % (int)(o->getGame()->getWindowWidth()-o->getWidth()); // para que no se pinte totalmente fuera de la pantalla 
		double y = rand() % (int)(o->getGame()->getWindowHeight()-o->getHeight());

		o->setPosition({ x,y });
	}
}
