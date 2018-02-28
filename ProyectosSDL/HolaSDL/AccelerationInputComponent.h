#pragma once
#include "InputComponent.h"
class AccelerationInputComponent :
	public InputComponent
{
protected:
	SDL_Keycode speedUp_;
	SDL_Keycode speedDown_;
public:
	AccelerationInputComponent(SDL_Keycode speedUp, SDL_Keycode speedDown);
	virtual ~AccelerationInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time,
		const SDL_Event& event);
};

