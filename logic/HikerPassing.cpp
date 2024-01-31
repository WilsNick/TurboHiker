//
// Created by nick on 31.12.20.
//

#include "HikerPassing.h"

namespace turbohiker {
    std::shared_ptr<Entity> HikerPassing::shout(double start, double length) {
        std::shared_ptr<RandomeNumber> r = r->getInstance();
        int percent = r->getintpercent();
//    update a knight when shouted at 25% move left, 25% move right, 50% do nothing
        if (knight) {
            if (percent <= 25) {
                setSpeedh(-1);
            } else if (percent <= 50) {
                setSpeedh(1);
            }
        } else {
//        update rat 50% do nothing, 50% chance multiply by 2 for some time
            if (percent <= 50) {
                if (!isBuffed()) {
                    setDebufftimer(getTimer() + 5000000);
                    setBuffed(true);
                    setMaxspeed(getMaxSpeed() * 2);
                    setSpeedv(getMaxSpeed());
                }
            }
        }
        return nullptr;
    }

    Coordinates HikerPassing::update() {
//    knight can only update horizontal
        int movedh = 0;
        if (knight) {
            if (getSpeedh() != 0) {
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
                setSpeedh(0);
            }
//    rat can only movedh up and down
        } else {
            Coordinates pos = getPosition();
            pos.y -= 0.0005 * getSpeedv() * (getDeltaTimer());
            setPosition(pos);
        }
        Coordinates toreturn = Coordinates(-movedh, 0.005 * getSpeedv() * (getDeltaTimer()));
        return toreturn;
    }

    void HikerPassing::removeBuff() {
        if (getBuffedTimer() < getTimer()) {
            setBuffed(false);
            setMaxspeed(getMaxSpeed() / 2);
            setSpeedv(getMaxSpeed());
        }
    }

    void HikerPassing::setKnight(bool h) {
        HikerPassing::knight = h;
    }
}
