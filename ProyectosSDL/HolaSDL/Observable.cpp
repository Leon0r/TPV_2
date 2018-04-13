#include "Observable.h"

void Observable::removeObserver(Observer * o)
{
	std::vector<Observer*>::iterator it;
	it = observers_.begin();
	while (it != observers_.end() && *it != o) it++;

	if (it != observers_.end())
		observers_.erase(it);
}
