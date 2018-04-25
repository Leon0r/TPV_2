#pragma once
#include "Container.h"
#include "Observable.h"
#include "Observer.h"
#include "ScoreRenderer.h"
#include "GameCtrlInputComponent.h"
#include "GameMsgRenderer.h"
#include "BadgeTimer.h"
#include "LifeRenderer.h"

const int LIVES = 3;
const int TIME_BADGE = 300;
class GameManager :
	public Container, public Observer, public Observable
{
	// maneja HUD (puntos, vidas...)
public:
	GameManager(SDLGame* game);
	virtual ~GameManager();

	virtual void update(Uint32 time) { badgeTimer.update(this, time); }

	bool isGameOver() const { return gameOver_; }
	int getLives()const { return lives_; }
	bool isRunning() const { return running_; }
	void setRunning(bool running);
	int getScore() const { return score_; };
	void setScore(int score) { score_ = score; }
	void setBadge(bool b) { badge_ = b; };
	void receive(Message* msg);


private:
	void asteroidFighterCollision();
	void bulletAsteroidCollision();
	void bulletBonusCollision(Message * msg);
	void noAsteroids();


	int score_ = 0;
	int asteroidsInRound = 0;
	int lives_ = LIVES;
	Fighter* fighter_;
	BadgeTimer badgeTimer;
	bool running_, gameOver_, badge_;
	ScoreRenderer scoreRender_;
	LifeRenderer lifesRender_;
	GameCtrlInputComponent gameCtrl_;
	GameMsgRenderer gameMsg_;
};

