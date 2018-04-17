#pragma once
#include "InputComponent.h"

class RotationInputComponent :
	public InputComponent
{
	// rota el objeto
public:
	RotationInputComponent(SDL_Keycode clock, SDL_Keycode counterClock);
	virtual ~RotationInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);

private:
	double angle = 5;
	SDL_Keycode clock_;
	SDL_Keycode counterClock_;
};

