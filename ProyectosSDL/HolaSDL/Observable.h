#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include "Observer.h"

class Observable
{
	std::vector<Observer*> observers_;

public:
	Observable() :observers_() {}
	virtual ~Observable() {}
	virtual void registerObserver(Observer* o) { observers_.push_back(o); }
	virtual void removeObserver(Observer* o);
	virtual void send(Message* msg) {
		for (Observer* o : observers_)
			o->receive(msg);
	}
};

#endif /* OBSERVABLE_H_ */