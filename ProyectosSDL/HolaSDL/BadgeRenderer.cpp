#include "BadgeRenderer.h"
#include "GameManager.h"

BadgeRenderer::BadgeRenderer()
{
}


BadgeRenderer::~BadgeRenderer()
{
}

void BadgeRenderer::render(GameObject * o, Uint32 time)
{
	GameManager* gm = static_cast<GameManager*>(o);

	SDLGame* game = gm->getGame();

	// draw lifes
	Texture* badge = game->getResources()->getImageTexture(Resources::Badges);
	int x = (badge->getWidth() / 3)*(badge_%3);
	int y = (badge->getHeight() / 3)*(badge_ / 3);
	int w = badge->getWidth() / 3;
	int h = badge->getHeight() / 3;

	SDL_Rect origR = { x, y, w, h };

	w = 30;
	h = 30;
	x = game->getWindowWidth() - 10 - w;
	y = 10;
	SDL_Rect destR = { x,y,w,h };

	badge->render(game->getRenderer(), destR, &origR);
}
