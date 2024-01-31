//
// Created by nick on 27.12.20.
//

#include "Entity.h"

namespace turbohiker {
    Entity::Entity() {
        subject = std::make_shared<Subject>();
        std::shared_ptr<ObserverInterface> o = std::make_shared<Observer>();
        subject->registerObserver(o);
        observer.push_back(o);
    }

    const Coordinates &Entity::getPosition() const {
        return position;
    }

    void Entity::setPosition(double x, double y) {
        position.x = x;
        position.y = y;
    }

    const Coordinates &Entity::getSize() const {
        return size;
    }

    void Entity::setSize(double x, double y) {
        size.x = x;
        size.y = y;
    }

    double Entity::getSpeedv() const {
        return speedv;
    }

    void Entity::setSpeedv(double s) {
//    check if the new speed does not go over the old speed
        if (maxspeed >= s and -maxspeed / 2 <= s) {
            speedv = s;
        } else {
            if (maxspeed < s) {
                speedv = maxspeed;
            } else {
                speedv = -maxspeed / 2;
            }
        }
    }

    void Entity::setPosition(const Coordinates &p) {
        Entity::position = p;
    }

    double Entity::getMaxSpeed() const {
        return maxspeed;
    }

    Coordinates Entity::GetHalfSize() const {
        Coordinates halfsize{getSize().x / 2.0f, getSize().y / 2.0f};
        return halfsize;
    }

    int Entity::getMyLane() const {
        return myLane;
    }

    void Entity::setMyLane(int l) {
        Entity::myLane = l;
    }

    int Entity::getSpeedh() const {
        return speedh;
    }

    void Entity::setSpeedh(int s) {
        Entity::speedh = s;
    }

    double Entity::getHeaviness() const {
        return heaviness;
    }

    void Entity::setHeaviness(double h) {
        Entity::heaviness = h;
    }

    bool Entity::isTransparent() const {
        return transparent;
    }

    void Entity::setTransparent(bool g) {
        Entity::transparent = g;
    }

    bool Entity::isSlowedDown() const {
        return slowedDown;
    }

    void Entity::setSlowedDown(bool s) {
        Entity::slowedDown = s;
    }

    bool Entity::isHasTextBubble() const {
        return hasTextBubble;
    }

    void Entity::setHasTextBubble(bool b) {
        Entity::hasTextBubble = b;
    }

    const std::shared_ptr<Entity> &Entity::getTextBubble() const {
        return textBubble;
    }

    void Entity::setTextBubble(const std::shared_ptr<Entity> &balloon) {
        Entity::textBubble = balloon;
    }

    bool Entity::isBuffed() const {
        return buffed;
    }

    void Entity::setBuffed(bool b) {
        Entity::buffed = b;
    }

    double Entity::getBuffedTimer() const {
        return buffedTimer;
    }

    void Entity::setDebufftimer(double bt) {
        Entity::buffedTimer = bt;
    }

    void Entity::setMaxspeed(double ms) {
        Entity::maxspeed = ms;
    }

    double Entity::getTimeLock() const {
        return timeLock;
    }

    void Entity::setTimeLock(double l) {
        Entity::timeLock = l;
    }

    bool Entity::isTimeLocked() const {
        return timeLocked;
    }

    void Entity::setTimeLocked(bool l) {
        Entity::timeLocked = l;
    }

    bool Entity::isWantToShout() const {
        return wantToShout;
    }

    void Entity::setWantToShout(bool ws) {
        Entity::wantToShout = ws;
    }

    double Entity::getTimer() const {
        return timer;
    }

    void Entity::setTimer(double t) {
        Entity::timer = t;
    }

    bool Entity::isObstacle() const {
        return obstacle;
    }

    void Entity::setObstacle(bool o) {
        Entity::obstacle = o;
    }

    double Entity::getDeltaTimer() const {
        return deltaTime;
    }

    void Entity::setDeltaTimer(double ot) {
        Entity::deltaTime = ot;
    }

    int Entity::getScore() const {
        int x = observer[0]->getScore();
        return x;
    }

    void Entity::setScore(int s) {
        subject->setScore(s);
    }

    const std::string &Entity::getScoreText() const {
        return scoreText;
    }

    void Entity::setScoreText(const int &s) {
        std::string s_text = std::to_string(s);
        Entity::scoreText = s_text;
    }

    bool Entity::isEnemy() const {
        return enemy;
    }

    void Entity::setEnemy(bool e) {
        Entity::enemy = e;
    }

    void Entity::Move(double dx, double dy) {
        setPosition(getPosition().x + dx, getPosition().y + dy);
    }

    void Entity::deleteSubject() {
        subject = nullptr;
        while (!observer.empty()) {
            observer.pop_back();
        }
    }
}