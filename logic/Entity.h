//
// Created by nick on 27.12.20.
//

#ifndef TURBOHIKER_ENTITY_H
#define TURBOHIKER_ENTITY_H

#include <memory>
#include <vector>
#include <algorithm>
#include "Coordinates.h"
#include "Singletons/Transformation.h"
#include "Singletons/RandomeNumber.h"
#include "Observer/SubjectInterface.h"
#include "Observer/Subject.h"
#include "Observer/Observer.h"

namespace turbohiker {
    /**
     * base class of entities in world, consist of getters setters and pure virtual functions
     */
    class Entity {
    public:

        /**
         * constructor
         */
        Entity();

        /**
         * destructor
         */
        virtual ~Entity() = default;

        /**
         * delete subject and observer
         */
        void deleteSubject();

        /**
         * pure virtual function
         * renders an object on window
         */
        virtual void render() = 0;

        /**
         * pure virtual function
         * update the logic position of an entity
         * @return Coordinates of how much is moved
         */
        virtual Coordinates update() = 0;

        /**
         * pure virtual function
         * update pixle position
         * @param s how much needs te be moved
         */
        virtual void updateVisuals(Coordinates s) = 0;

        /**
         * pure virtual function
         * move position for updated view
         * @param s how much needs te be moved
         */
        virtual void moveToView(double s) = 0;

        /**
         * pure virtual function
         * speedup entity
         * @param x integer: 1 if right, -1 if move left else 0
         * @param y integer: 1 if up, -1 if move down else 0
         */
        virtual void speedup(int x, int y) = 0;

        /**
         * pure virtual function
         * handles when an entity wants to shout or is shouted at
         * @return entity text bubble
         */
        virtual std::shared_ptr<Entity> shout(double, double) = 0;

        /**
         * pure virtual function
         * remove a buff
         */
        virtual void removeBuff() = 0;

        /**
         * pure virtual function
         * remove text bubble if time lock is over
         * @param force bool true if the text bubble needs to be removed regardless of the lock
         * @return entity text bubble that is removed
         */
        virtual std::shared_ptr<Entity> removeShout(bool force) = 0;

        /**
         * getter position logic
         * @return  coordinats of player
         */
        const Coordinates &getPosition() const;

        /**
         * move a position logic to dx, dy
         * @param dx double x pos
         * @param dy  double y pos
         */
        void Move(double dx, double dy);

        /**
         * setter position logic
         * @param x double x pos
         * @param y  double y pos
         */
        void setPosition(double x, double y);

        /**
         * setter position logix
         * @param position the new coordinats
         */
        void setPosition(const Coordinates &position);

        /**
         * getter size
         * @return coordinats
         */
        const Coordinates &getSize() const;

        /**
         * setter size
         * @param x double x width
         * @param y double y length
         */
        void setSize(double x, double y);

        /**
         * getter vertical speed
         * @return double
         */
        double getSpeedv() const;

        /**
         * setter vertical speed
         * @param speed double
         */
        void setSpeedv(double speed);

        /**
         * getter maxspeed
         * @return double
         */
        double getMaxSpeed() const;

        /**
         * setter maxspeed
         * @param maxspeed double
         */
        void setMaxspeed(double maxspeed);

        /**
         * getter the lane this entity is in
         * @return  int
         */
        int getMyLane() const;

        /**
         * getter the lane this entity is in
         * @param mylane int
         */
        void setMyLane(int mylane);

        /**
         * getter half of the size for collision detection
         * @return coordinates
         */
        Coordinates GetHalfSize() const;

        /**
         * getter heaviness
         * @return double
         */
        double getHeaviness() const;

        /**
         * setter heaviness
         * @param h double
         */
        void setHeaviness(double h);

        /**
         * getter transparency
         * @return true is transparent
         */
        bool isTransparent() const;

        /**
         * setter transparency
         * @param g bool
         */
        void setTransparent(bool g);

        /**
         * getter if entity slows down
         * @return bool
         */
        bool isSlowedDown() const;

        /**
         * setter if entity slows down
         * @param s bool
         */
        void setSlowedDown(bool s);

        /**
         * getter if entity has a text bubble
         * @return bool
         */
        bool isHasTextBubble() const;

        /**
         * setter if entity has a text bubble
         * @param t
         */
        void setHasTextBubble(bool t);

        /**
         * getter text bubble linked with this entity
         * @return entity
         */
        const std::shared_ptr<Entity> &getTextBubble() const;

        /**
         * setter text bubble linked with this entity
         * @param t entity
         */
        void setTextBubble(const std::shared_ptr<Entity> &t);

        /**
         * getter if entity is buffed
         * @return boolean
         */
        bool isBuffed() const;

        /**
         * setter if entity is buffed
         * @param d  boolean
         */
        void setBuffed(bool d);

        /**
         * getter debuff timer
         * @return double
         */
        double getBuffedTimer() const;

        /**
         * setter debuf timer
         * @param debufftimer double
         */
        void setDebufftimer(double debufftimer);

        /**
         * getter locked until
         * @return double
         */
        double getTimeLock() const;

        /**
         * setter lock until time
         * @param lock double
         */
        void setTimeLock(double lock);

        /**
         * getter if locked
         * @return bool
         */
        bool isTimeLocked() const;

        /**
         * setter if locked
         * @param locked bool
         */
        void setTimeLocked(bool locked);

        /**
         * get if entity wants to shout
         * @return bool
         */
        bool isWantToShout() const;

        /**
         * set if entity wants toshout
         * for enemy
         * @param wannashout bool
         */
        void setWantToShout(bool wannashout);

        /**
         * get game time
         * @return double
         */
        double getTimer() const;

        /**
         * setter game time
         * @param timer double
         */
        void setTimer(double timer);

        /**
         * getter is entity is an obstacle
         * @return bool
         */
        bool isObstacle() const;

        /**
         * setter if  entity is an obstacle
         * @param isobstacle
         */
        void setObstacle(bool isobstacle);

        /**
         * getter delta timer = time between rounds
         * @return double
         */
        double getDeltaTimer() const;

        /**
         * set delta timer = the time between rounds
         * @param d double
         */
        void setDeltaTimer(double d);

        /**
         * get score from observer
         * @return int
         */
        int getScore() const;

        /**
         * set score in observer
         * @param score int
         */
        void setScore(int score);

        /**
         * getter score in string
         * @return string
         */
        const std::string &getScoreText() const;

        /**
         * setter score in string
         * @param scoring bool
         */
        void setScoreText(const int &scoring);

        /**
         * getter if entity is an enemy
         * @return bool
         */
        bool isEnemy() const;

        /**
         * setter if entity is an enemy
         * @param enemy bool
         */
        void setEnemy(bool enemy);

        /**
         * getter horizontal speed
         * @return  int
         */
        int getSpeedh() const;

        /**
         * setter horizontal speed
         * @param speedh int
         */
        void setSpeedh(int speedh);

    private:
        std::string scoreText;
        std::shared_ptr<SubjectInterface> subject;
        std::vector<std::shared_ptr<ObserverInterface>> observer;
        Coordinates position{0, 0};
        Coordinates size{0, 0};
        double maxspeed = 120;
        double speedv = 0;
        int speedh = 0;
        double timer = 0;
//        time between rounds
        double deltaTime = 0;
//    percentage of how much a hiker will move in collision
        double heaviness = 0;
//    true if it has no collision
        bool transparent = false;
//    true if hiker needs to slow down when touched
        bool slowedDown = false;
//    buff of a hiker
        bool buffed = false;
        double buffedTimer = 0;
//    text bubble if yelled
        bool hasTextBubble = false;
        std::shared_ptr<Entity> textBubble = nullptr;
//    lock on knight movement speed
        double timeLock = 0;
        bool timeLocked = false;
//    ai wants to shout
        bool wantToShout = false;
//    entity is an obstacle
        bool obstacle = false;
//    entity is an enemy
        bool enemy = false;
//    lane of the hiker
        int myLane = -1;
    };
}

#endif //TURBOHIKER_ENTITY_H
