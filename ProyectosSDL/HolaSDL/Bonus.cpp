#include "Bonus.h"



Bonus::Bonus(SDLGame* game):Container(game)
{
	addRenderComponent(new ImageRenderer(game->getResources()->getImageTexture(Resources::Star)));
	addPhysicsComponent(new RandomMotionPhysics(3000));
	addPhysicsComponent(new RotationPhysics(10));
	setActive(false);
	setWidth(50);
	setHeight(50);
	

}


Bonus::~Bonus()
{
}

void Bonus::receive(Message * msg)
{
	switch (msg->id_) {
	case ROUND_START:
		setActive(true);
		break;
	case BULLET_BONUS_COLLISION:
		setActive(false);
		break;
	case GAME_OVER:
		setActive(false);
		break;
	case ROUND_OVER:
		setActive(false);
		break;
	}
}