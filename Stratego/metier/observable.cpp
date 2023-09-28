#include "observable.h"
using namespace utils;
using namespace observable;
using namespace observers;
using namespace std;

void Observable::notify(const std::string & toUpdate) const{
    for(auto * observer: this->observers){
        observer->update(toUpdate);
    }
}

void Observable::subscribe(Observers * observer){
    this->observers.insert(observer);
}

void Observable::unsubscribe(Observers * observer){
    this->observers.erase(observer);
}
