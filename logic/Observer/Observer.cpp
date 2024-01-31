//
// Created by nick on 04.01.21.
//

#include "Observer.h"

namespace turbohiker {
    void Observer::update(int s) {
        score += s;

    }

    int Observer::getScore() {
        return (int) score;
    }
}