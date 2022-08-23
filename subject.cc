#include "subject.h"
#include "observer.h"

using namespace std;

Subject::Subject() {}
Subject::~Subject() {}

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

void Subject::notifyObservers() {
  for (auto ob : observers) {
    ob->notify(*this);
  }
}
