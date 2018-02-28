#pragma once
#include "InputComponent.h"
class RotationInputComponent :
	public InputComponent
{
protected:
	double angle; 
	SDL_Keycode Clock, CounterClock;

public:
	RotationInputComponent(double angle, SDL_Keycode Clock, SDL_Keycode CounterClock) : angle(angle), Clock(Clock), CounterClock(CounterClock) {}
	~RotationInputComponent();

	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};

