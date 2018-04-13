#include "AccelerationInputComponent.h"



AccelerationInputComponent::AccelerationInputComponent(SDL_Keycode speedUp, SDL_Keycode speedDown, double thrust, double maxVel, double redFactor):
	speedDown_(speedDown),speedUp_(speedUp), thrust_(thrust), maxVel_(maxVel), reducFactor_(redFactor)
{
}


AccelerationInputComponent::~AccelerationInputComponent()
{
}

void AccelerationInputComponent::handleInput(GameObject * o, Uint32 time, const SDL_Event & event)
{
	// con la W acelera y con la S frena
	if (event.type == SDL_KEYDOWN) {
		Vector2D velAux;
		velAux = o->getVelocity();

		if (event.key.keysym.sym == speedUp_) {
			velAux = o->getVelocity() + (o->getDirection()*thrust_);
			if (velAux.magnitude() >= maxVel_) {
				velAux.normalize();
				velAux = velAux * maxVel_;
			}
		}
		else if (event.key.keysym.sym == speedDown_) {
			if (velAux.magnitude() < limitMagnitude_)
				velAux = { 0,0 };

			velAux = o->getVelocity();
			velAux = velAux * reducFactor_;
		}
		if (velAux.magnitude() < limitMagnitude_)
			velAux = { 0,0 };
		o->setVelocity(velAux);
	}
}