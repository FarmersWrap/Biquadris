#ifndef _OBESERVER_H_
#define _OBESERVER_H_

#include <memory>

class Subject;

class Observer {
	public:
		Observer();
		virtual void notify(Subject &whoNotified) = 0;
		virtual ~Observer();
};

#endif 
