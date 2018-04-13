#include "LifeRenderer.h"
#include "GameManager.h"

LifeRenderer::LifeRenderer()
{
}


LifeRenderer::~LifeRenderer()
{
}

void LifeRenderer::render(GameObject * o, Uint32 time)
{
	GameManager* gm = static_cast<GameManager*>(o);

	SDLGame* game = gm->getGame();

	// draw lifes
	Texture* lifes = game->getResources()->getImageTexture(Resources::Badges);
	int x = (lifes->getWidth() / 3) * 2;
	int y = (lifes->getHeight() / 3) * 2;
	int w = lifes->getWidth() / 3;
	int h = lifes->getHeight() / 3;

	SDL_Rect origR = { x, y, w, h };

	y = 10;
	w = 30;
	h = 30;
	SDL_Rect destR = { x,y,w,h };

	int l = gm->getLives();
	for (int i = 0; i < l; i++) {
		destR.x = 10 + (w*i);
		lifes->render(game->getRenderer(), destR, &origR);
	}
}
