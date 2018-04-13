#include "BulletsManager.h"



BulletsManager::BulletsManager()
{
}


BulletsManager::~BulletsManager()
{
	for (Bullet* b : bullets_)
		delete b;
}
