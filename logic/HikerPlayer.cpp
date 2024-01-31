//
// Created by nick on 31.12.20.
//

#include "HikerPlayer.h"

namespace turbohiker {
    void HikerPlayer::speedup(int speedup, int speedh) {
        double currentSpeed = getSpeedv();
//    if speed is 0 start slowing down
        if (speedup == 0) {
            if (currentSpeed > 0) {

                currentSpeed -= (getDeltaTimer());
            } else if (currentSpeed < 0) {

                currentSpeed += (getDeltaTimer());
            }
        }
//    if your speed is in the other direction slow down harder
        if (speedup > 0 and 0 > currentSpeed) {
            currentSpeed += (2 * (getDeltaTimer()));
        }
        if (speedup < 0 and 0 < currentSpeed) {
            currentSpeed -= (2 * (getDeltaTimer()));
        }
//    update speed
        currentSpeed += (speedup * (getDeltaTimer()));
        setSpeedv(currentSpeed);
        setSpeedh(speedh);
    }


    std::shared_ptr<Entity> HikerPlayer::shout(double start, double length) {
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

    Coordinates HikerPlayer::update() {
//    movedh is 0 if player didn't switch lane, 1 if right, -1 if left
        int movedh = 0;
//    update the lane where the player is in if needed
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
//    update the y pos of the player with the speed
        Coordinates pos = getPosition();
        pos.y -= 0.0005 * getSpeedv() * (getDeltaTimer());
        if (pos.y > 3) {
            pos.y = 3;
        }
        setPosition(pos);
        Coordinates toreturn = Coordinates(-movedh, 0.005 * getSpeedv() * (getDeltaTimer()));
        return toreturn;
    }

    void HikerPlayer::removeBuff() {
        if (getBuffedTimer() < getTimer()) {
            setBuffed(false);
            setMaxspeed(getMaxSpeed() * 2);
        }
    }
}
