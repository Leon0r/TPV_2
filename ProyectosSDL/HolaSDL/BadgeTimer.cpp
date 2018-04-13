#include "BadgeTimer.h"
#include "GameManager.h"

BadgeTimer::BadgeTimer()
{
}


BadgeTimer::~BadgeTimer()
{
}

void BadgeTimer::update(GameObject* o, Uint32 time)
{
	if (on_ && (timeOn_ + timeInterval_) > time) {
		static_cast<GameManager*>(o)->setBadge(false);
		on_ = false;
	}
}

void BadgeTimer::start(Uint32 timeInterval)
{
	on_ = true;
	timeOn_ = SDL_GetTicks();
	timeInterval_ = timeInterval;
}
