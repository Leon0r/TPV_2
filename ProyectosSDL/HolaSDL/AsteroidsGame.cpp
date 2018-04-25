#include "AsteroidsGame.h"


// llama a las constructoras de los objetos de los managers. 
// solo es necesario si el obj no tiene constructora predeterminada (sin parametros)
AsteroidsGame::AsteroidsGame():
	SDLGame("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_),
	bulletsManager_(StarTreckBulletsManager(this)), fightersManager_(FightersManager(this, &bulletsManager_)),
	asteroidsManager_ (AsteroidsManager(this)), collisionManager_ (CollisionManager(this, &asteroidsManager_, &bulletsManager_, &fightersManager_,&bonus_)),
	gameManager_(GameManager(this)),soundManager_(SoundManager(this)), bonus_(Bonus(this))
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

	// añade observers

	collisionManager_.registerObserver(&gameManager_);
	collisionManager_.registerObserver(&asteroidsManager_);
	collisionManager_.registerObserver(&bulletsManager_);
	collisionManager_.registerObserver(&soundManager_);
	collisionManager_.registerObserver(&bonus_);

	asteroidsManager_.registerObserver(&gameManager_);

	bulletsManager_.registerObserver(&gameManager_);
	bulletsManager_.registerObserver(&soundManager_);

	gameManager_.registerObserver(&fightersManager_);
	gameManager_.registerObserver(&bulletsManager_);
	gameManager_.registerObserver(&asteroidsManager_);
	gameManager_.registerObserver(&soundManager_);
	gameManager_.registerObserver(&bonus_);

	// añade los managers a la lista de actores en el orden en el que hay que actualizarlos
	actors_.push_back(&bonus_);
	actors_.push_back(&bulletsManager_);
	actors_.push_back(&fightersManager_);
	actors_.push_back(&asteroidsManager_);
	actors_.push_back(&collisionManager_);
	actors_.push_back(&gameManager_);
}

void AsteroidsGame::closeGame()
{
}

// bucle del juego
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
			// Pressing f to toggle fullscreen. (sigue sin funcionar sin razon aparente)
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
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00000000)); // el fondo se pinta negro
	SDL_RenderClear(getRenderer());

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}
