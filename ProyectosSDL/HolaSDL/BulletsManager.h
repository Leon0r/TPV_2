#pragma once
#include "Observer.h"
#include "Observable.h"

class BulletsManager :
	public Observer, public Observable
{
public:
	BulletsManager();
	virtual ~BulletsManager();
	virtual vector<Bullet*>& getBullets() = 0;

protected:
	vector<Bullet*> bullets_;
};

