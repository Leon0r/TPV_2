#pragma once
#include "SDLGame.h"
#include "StarTreckBulletsManager.h"
#include "FightersManager.h"
#include "CollisionManager.h"
#include "AsteroidsManager.h"
#include "GameManager.h"
#include "SoundManager.h"

class AsteroidsGame :
	public SDLGame
{
public:
	AsteroidsGame();
	virtual ~AsteroidsGame();

	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	const static int _WINDOW_WIDTH_ = 800;
	const static int _WINDOW_HEIGHT_ = 600;
	bool exit_;
	std::vector<GameObject*> actors_;

	StarTreckBulletsManager bulletsManager_;
	FightersManager fightersManager_;
	AsteroidsManager asteroidsManager_;
	CollisionManager collisionManager_;
	GameManager gameManager_;
	SoundManager soundManager_;
};

