#pragma once
#include "Container.h"
class Asteroid :
	public Container
{
	// solo guarda la generacion (nivel) del asteroide, los demas componentes estan en el manager de asteroides
public:
	Asteroid(SDLGame* game);
	virtual ~Asteroid();
	virtual void setGenerations(int generations) { generations_ = generations; }
	virtual int getGenerations() { return generations_; }
	
private:
	int generations_;
};

