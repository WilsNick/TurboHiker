//
// Created by nick on 27.12.20.
//

#include "Hiker.h"

namespace turbohiker {
    void Hiker::moveToView(double moved) {
        Coordinates pos = getPosition();
        pos.y -= moved;
        setPosition(pos);
    }

    int Hiker::getAllLaneCount() const {
        return allLaneCount;
    }

    void Hiker::setAllLaneCount(int l) {
        Hiker::allLaneCount = l;
    }

    std::shared_ptr<Entity> Hiker::removeShout(bool force) {
        if (shoutlock) {
            if (getTimer() > shoutLockTimer or force) {
                shoutlock = false;
                std::shared_ptr<Entity> b = getTextBubble();
                setTextBubble(nullptr);
                setHasTextBubble(false);
                return b;
            }
        }
        return nullptr;
    }

    void Hiker::setBubbleFact(const std::shared_ptr<LayoutFactory> &fact) {
        Hiker::bubbleFact = fact;
    }

    const std::shared_ptr<LayoutFactory> &Hiker::getBubbleFact() const {
        return bubbleFact;
    }

    bool Hiker::isShoutlock() const {
        return shoutlock;
    }

    void Hiker::setShoutlock(bool s) {
        Hiker::shoutlock = s;
    }

    void Hiker::setShoutLockedtimer(double l) {
        Hiker::shoutLockTimer = l;
    }

    void Hiker::setScoretext(const std::shared_ptr<Entity> &s) {
        Hiker::scoretext = s;
    }

    const std::shared_ptr<Entity> &Hiker::getScoretext() const {
        return scoretext;
    }
}
