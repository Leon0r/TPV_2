#include "GameManager.h"



GameManager::GameManager(SDLGame* game):Container(game)
{
	setRunning(false);
	addRenderComponent(&scoreRender_);
	addRenderComponent(&lifesRender_);
	addInputComponent(&gameCtrl_);
	addRenderComponent(&gameMsg_);
}


GameManager::~GameManager()
{
}

void GameManager::setRunning(bool running)
{
	if (running_ != running) {
		running_ = running;

		Message m = { running ? ROUND_START : ROUND_OVER };
		send(&m);
		if (gameOver_ && running)
			gameOver_ = false;
	}
}

void GameManager::receive(Message * msg)
{
	switch (msg->id_) {
	case ASTROID_FIGHTER_COLLISION:
		asteroidFighterCollision();
		break; 
	case BULLET_ASTROID_COLLISION:
		bulletAsteroidCollision();
		break;
	case BULLET_BONUS_COLLISION:
		bulletBonusCollision(msg);
		break;
	case NO_MORE_ATROIDS:
		noAsteroids();
		break;
	}
}

void GameManager::asteroidFighterCollision()
{
	lives_--;
	badge_ = false;
	send(&Message(BADGE_OFF));

	if (lives_ > 0) {
		running_ = false;
		asteroidsInRound = 0;
		send(&Message(ROUND_OVER));
	}
	else {
		gameOver_ = true;
		send(&Message(GAME_OVER));
	}
}

void GameManager::bulletAsteroidCollision()
{
	if (!gameOver_) {
		score_++;
		asteroidsInRound++;
		if (asteroidsInRound >= 10) {
			badge_ = true;
			Message msg(BadgeIsOn(fighter_->getWeapon()));
			send(&msg);
			badgeTimer.start(TIME_BADGE); // activa el timer
		}
	}
}

void GameManager::bulletBonusCollision(Message * msg)
{
	if (lives_ > 0) {
		BulletBonusCollision * a = static_cast<BulletBonusCollision*>(msg);
		a->bullet_->setActive(false);
		lives_++;
	}

}

void GameManager::noAsteroids()
{
	badge_ = false;
	running_ = false;
	send(&Message(BADGE_OFF));
	send(&Message(GAME_OVER));
}

