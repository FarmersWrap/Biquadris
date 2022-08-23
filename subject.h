#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <memory>
#include <vector>

class Observer;

class Subject {
    public:
      Subject();
      void attach(Observer *o);  
      void notifyObservers();
      virtual ~Subject() = 0;
    private:  
      std::vector<Observer *> observers;
};

#endif 
