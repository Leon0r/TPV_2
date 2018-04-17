#include "StarTreckBulletsManager.h"



StarTreckBulletsManager::StarTreckBulletsManager(SDLGame* game):GameObject(game),
bulletRenderer_ (FillRectRenderer({ COLOR(0xffffffff) }))
{
}


StarTreckBulletsManager::~StarTreckBulletsManager()
{
}

void StarTreckBulletsManager::update(Uint32 time)
{
	for (Bullet* b : bullets_)
		if (b->isActive()) {
			if (!isOutOfBounds(b))
				b->update(time);
			else
				b->toggleActive();
		}
}

void StarTreckBulletsManager::render(Uint32 time)
{
	for (Bullet* b : bullets_)
		if (b->isActive())
			b->render(time);
}

Bullet * StarTreckBulletsManager::getBulletDead()
{
	vector<Bullet*>::iterator it;
	it = bullets_.begin();
	while (it != bullets_.end() && (*it)->isActive()) it++;

	if (it == bullets_.end()) {
		bullets_.push_back(new Bullet(game_));
		bullets_.back()->setActive(false);
		return bullets_.back();
	}
	else
		return (*it);
}

void StarTreckBulletsManager::receive(Message * msg)
{
	switch (msg->id_) {
	case ROUND_START:
		deactivateBullets();
		break;
	case ROUND_OVER:
		deactivateBullets();
		break;
	case BULLET_ASTROID_COLLISION: {
		BulletAstroidCollision * a = static_cast<BulletAstroidCollision*>(msg);
		a->bullet_->setActive(false);
		break;
	}
	case BULLET_FIGHTER_COLLISION:{
		BulletFighterCollision * a = static_cast<BulletFighterCollision*>(msg);
		a->bullet_->setActive(false);
		break;
	}
	case FIGHTER_SHOOT: {
		FighterIsShooting* a = static_cast<FighterIsShooting*>(msg);
		shoot(a->fighter_, a->bulletPosition_, a->bulletVelocity_);
		break;
	}
	}
}

void StarTreckBulletsManager::shoot(Fighter * owner, Vector2D pos, Vector2D vel)
{
	Bullet* aux = getBulletDead();
	aux->addRenderComponent(&bulletRenderer_);
	aux->addPhysicsComponent(&bulletPhysics_);

	Vector2D a = vel;
	a.normalize();

	aux->setDirection(a);
	aux->setFighterID(owner->getID());
	aux->setPosition(pos);
	aux->setVelocity(vel);

	aux->setWidth(4);
	aux->setHeight(4);
	aux->setActive(true);
	send(&Message(BULLET_CREATED));
}

void StarTreckBulletsManager::deactivateBullets()
{
	for (Bullet* b : bullets_)
		b->setActive(false);
}

bool StarTreckBulletsManager::isOutOfBounds(Bullet * b)
{
	if (b->getPosition().getY() > game_->getWindowHeight() || b->getPosition().getX() > game_->getWindowWidth() ||
		b->getPosition().getX() < 0 || b->getPosition().getY() < 0)
		return true;
	return false;
}
