#pragma once
#include "InputComponent.h"

class AccelerationInputComponent :
	public InputComponent
{
public:
	AccelerationInputComponent(SDL_Keycode speedUp, SDL_Keycode speedDown, double thrust, double maxVel, double redFactor);
	virtual ~AccelerationInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
private:
	double thrust_;
	double maxVel_;
	double reducFactor_;
	const double limitMagnitude_ = 0.1;
	SDL_Keycode speedUp_; 
	SDL_Keycode speedDown_;
};

