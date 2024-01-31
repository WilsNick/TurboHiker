//
// Created by nick on 30.12.20.
//

#include "Collider.h"

namespace turbohiker {
    bool Collider::CheckCollision(const std::shared_ptr<Entity> &first, const std::shared_ptr<Entity> &other) {
        Coordinates otherPosition = other->getPosition();
        Coordinates otherHalfSize = other->GetHalfSize();
        Coordinates thisPosition = first->getPosition();
        Coordinates thisHalfSize = first->GetHalfSize();

        double deltaY = otherPosition.y - thisPosition.y;
        double intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        return first->getMyLane() == other->getMyLane() && intersectY < 0.0f;
    }


    bool
    Collider::checklaneswitch(const std::shared_ptr<Entity> &first, const std::shared_ptr<Entity> &other, bool left) {
        Coordinates otherPosition = other->getPosition();
        Coordinates otherHalfSize = other->GetHalfSize();
        Coordinates thisPosition = first->getPosition();
        Coordinates thisHalfSize = first->GetHalfSize();

        double deltaY = otherPosition.y - thisPosition.y;
        double intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        if (intersectY < 0.0f) {
            if (left) {
                if (first->getMyLane() - 1 == other->getMyLane()) {
                    return false;
                }
            } else {
                if (first->getMyLane() + 1 == other->getMyLane()) {
                    return false;
                }
            }
        }
        return true;
    }

    std::vector<double>
    Collider::CollisionDetection(std::shared_ptr<Entity> &first, std::shared_ptr<Entity> &other) {

        Coordinates otherPosition = other->getPosition();
        Coordinates otherHalfSize = other->GetHalfSize();
        Coordinates thisPosition = first->getPosition();
        Coordinates thisHalfSize = first->GetHalfSize();

        double deltaY = otherPosition.y - thisPosition.y;
        double intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
        double movedBackFirst = 0;
        double movedBackOther = 0;
//    if in collision
        if (first->getMyLane() == other->getMyLane() && intersectY < 0.0f) {
//        see how much each hiker needs to move back
            movedBackFirst = intersectY * (first->getHeaviness() / (other->getHeaviness() + first->getHeaviness()));
            movedBackOther = intersectY * (other->getHeaviness() / (other->getHeaviness() + first->getHeaviness()));
//        if you toch a rat you need to slow down
            if (first->isSlowedDown() and !other->isTransparent()) {
                if (!other->isBuffed()) {
                    other->setMaxspeed(other->getMaxSpeed() / 2);
                    other->setBuffed(true);
                    other->setDebufftimer(other->getTimer() + other->getTimer());
                }
            }
            if (other->isSlowedDown() and !first->isTransparent()) {
                if (!first->isBuffed()) {
                    first->setMaxspeed(first->getMaxSpeed() / 2);
                    first->setBuffed(true);
                    first->setDebufftimer(first->getTimer() + 5000000);
                }
            }
//        if you toch a transparent object you dont need to move back
            if (first->isTransparent()) {
                return {0, 0};
            } else if (other->isTransparent()) {
                return {0, 0};
            }
//        move back the objects
            if (deltaY > 0.0f) {
                movedBackOther *= -1;
                first->Move(0.0f, movedBackFirst);
                other->Move(0.0f, movedBackOther);
            } else {
                movedBackFirst *= -1;
                first->Move(0.0f, movedBackFirst);
                other->Move(0.0f, movedBackOther);
            }
            return {movedBackFirst, movedBackOther};
        }
        return {movedBackFirst, movedBackOther};
    }
}
