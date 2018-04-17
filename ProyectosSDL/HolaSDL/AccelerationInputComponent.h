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
	double thrust_; // impulso de aceleracion
	double maxVel_; // velocidad maxima
	double reducFactor_; // factor de desaceleracion
	const double limitMagnitude_ = 0.1; // para que cuando vel.magnitude sea menor que este, se ponga a 0 y no se mueva pixel a pixel
	SDL_Keycode speedUp_; // teclas de acelerar/desacelerar
	SDL_Keycode speedDown_;
};

