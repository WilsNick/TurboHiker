//
// Created by nick on 04.01.21.
//

#include "Subject.h"

namespace turbohiker {
    void Subject::registerObserver(std::shared_ptr<ObserverInterface> &observer) {
        observers.push_back(observer);
    }

    void Subject::notifyObservers() {
        for (auto &o : observers) {
            o->update(value);
        }
    }

    void Subject::setScore(int s) {
        value = s;
        notifyObservers();
    }

    Subject::~Subject() {
        while (!observers.empty()) {
            observers.pop_back();
        }
    }
}
