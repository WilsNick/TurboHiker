//
// Created by nick on 31.12.20.
//

#include "HikerEnemy.h"

namespace turbohiker {
    void HikerEnemy::speedup(int speedv, int speedh) {
//  speedv 1 if obstacle in front else 0
//  speedh 3 if obstacle left and right, 2 if obstacle left, 1 if obstacle right else 0
        std::shared_ptr<RandomeNumber> r = r->getInstance();
        int precent = r->getintpercent();
        int setspeedh = 0;
//    only update if ther is an obstacle in front of enemy
        if (speedv == 1) {
//        if not other option shout
            if (speedh == 3) {
                setWantToShout(true);
//        try to move to the left or shout
            } else if (speedh == 2) {
                if (precent > 99) {
                    setWantToShout(true);

                } else {
                    if (isTimeLocked()) {
                        setWantToShout(true);
                    } else {
                        setTimeLock(getTimer() + 600000);
                        setTimeLocked(true);
                        setspeedh = -1;
                    }
                }
//        try to move to the right or shout
            } else if (speedh == 1) {
                if (precent > 99) {
                    setWantToShout(true);
                } else {
                    if (isTimeLocked()) {
                        setWantToShout(true);
                    } else {
                        setTimeLock(getTimer() + 600000);
                        setTimeLocked(true);
                        setspeedh = 1;
                    }
                }
//        try to move to the left or right or shout
            } else {
                int x = (precent <= 40) ? 1 : -1;
                if (precent > 99) {
                    setWantToShout(true);
                } else {
                    if (isTimeLocked()) {
                        setWantToShout(true);
                    } else {
                        setTimeLock(getTimer() + 600000);
                        setTimeLocked(true);
                        setspeedh = x;
                    }
                }
            }
        }
        double currentSpeed = (getSpeedv());
        currentSpeed += getDeltaTimer();
        setSpeedv(currentSpeed);
        setSpeedh(setspeedh);
    }

    std::shared_ptr<Entity> HikerEnemy::shout(double start, double length) {
        if (!isShoutlock()) {
            setShoutlock(true);
            Coordinates size{getSize().x - 4, getSize().y - 3};
            Coordinates pos{start + length * getMyLane(), getPosition().y - 0.5};
            std::shared_ptr<Entity> b = getBubbleFact()->createProp(size, pos);
            setTextBubble(b);
            setShoutLockedtimer(getTimer() + 2000000);
            setHasTextBubble(true);
            return b;
        }
        return nullptr;
    }

    Coordinates HikerEnemy::update() {
        int movedh = 0;
//    move lanes
        if (getSpeedh() > 0) {
            if (getMyLane() < getAllLaneCount()) {
                setMyLane(getMyLane() + 1);
                movedh += 1;
            }
        } else if (getSpeedh() < 0) {
            if (getMyLane() != 0) {
                setMyLane(getMyLane() - 1);
                movedh -= 1;
            }
        }
//    move up and down
        Coordinates pos = getPosition();
        pos.y -= 0.0005 * getSpeedv() * (getDeltaTimer());
        setPosition(pos);
        Coordinates toreturn = Coordinates(-movedh, 0.005 * getSpeedv() * (getDeltaTimer()));
        return toreturn;
    }

    void HikerEnemy::removeBuff() {
        if (getBuffedTimer() < getTimer()) {
            setBuffed(false);
            setMaxspeed(getMaxSpeed() * 2);
        }
    }
}