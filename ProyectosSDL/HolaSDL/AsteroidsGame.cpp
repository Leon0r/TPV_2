#include "AsteroidsGame.h"



AsteroidsGame::AsteroidsGame():
	SDLGame("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_),
	bulletsManager_(StarTreckBulletsManager(this)), fightersManager_(FightersManager(this, &bulletsManager_)),
	asteroidsManager_ (AsteroidsManager(this)), collisionManager_ (CollisionManager(this, &asteroidsManager_, &bulletsManager_, &fightersManager_)),
	gameManager_(GameManager(this)),soundManager_(SoundManager(this))
{
	initGame();
	exit_ = false;
}


AsteroidsGame::~AsteroidsGame()
{
	closeGame();
}

void AsteroidsGame::initGame()
{
	SDL_ShowCursor(0);

	collisionManager_.registerObserver(&gameManager_);
	collisionManager_.registerObserver(&asteroidsManager_);
	collisionManager_.registerObserver(&bulletsManager_);
	collisionManager_.registerObserver(&soundManager_);

	asteroidsManager_.registerObserver(&gameManager_);

	bulletsManager_.registerObserver(&gameManager_);
	bulletsManager_.registerObserver(&soundManager_);

	gameManager_.registerObserver(&fightersManager_);
	gameManager_.registerObserver(&bulletsManager_);
	gameManager_.registerObserver(&asteroidsManager_);
	gameManager_.registerObserver(&soundManager_);

	actors_.push_back(&bulletsManager_);
	actors_.push_back(&fightersManager_);
	actors_.push_back(&asteroidsManager_);
	actors_.push_back(&collisionManager_);
	actors_.push_back(&gameManager_);
}

void AsteroidsGame::closeGame()
{
}

void AsteroidsGame::start()
{
	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();
		handleInput(startTime);
		update(startTime);

		render(startTime);
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void AsteroidsGame::stop()
{
	exit_ = true;
}

void AsteroidsGame::handleInput(Uint32 time)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			exit_ = true;
			break;
			// Pressing f to toggle fullscreen.
		case SDLK_f:
			int flags = SDL_GetWindowFlags(window_);
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(window_, 0);
			}
			else {
				SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
			}
			break;
		}
		for (GameObject* o : actors_) {
			o->handleInput(time, event);
		}
	}
}

void AsteroidsGame::update(Uint32 time)
{
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void AsteroidsGame::render(Uint32 time)
{
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00000000));
	SDL_RenderClear(getRenderer());

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}
