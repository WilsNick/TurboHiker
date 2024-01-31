//
// Created by nick on 27.12.20.
//

#ifndef TURBOHIKER_HIKER_H
#define TURBOHIKER_HIKER_H


#include "Entity.h"
#include "Layout.h"
#include "Factories/LayoutFactory.h"

namespace turbohiker {
    /**
     * hiker is derived from entity and is parent to all hikers
     */
    class Hiker : public Entity {
    public:
        /**
         * constructor
         */
        Hiker() = default;

        /**
         * destructor
         */
        ~Hiker() override {
            scoretext = nullptr;
            bubbleFact = nullptr;
        };

        /**
         * move position for updated view
         * @param m how much needs te be moved
         */
        void moveToView(double m) override;

        /**
         * remove text bubble if time lock is over
         * @param force bool true if the text bubble needs to be removed regardless of the lock
         * @return entity text bubble that is removed
         */
        std::shared_ptr<Entity> removeShout(bool force) override;

        /**
         * getter of total of lanes
         * @return int
         */
        int getAllLaneCount() const;

        /**
         * setter of total of lanes
         * @param lanes int
         */
        void setAllLaneCount(int lanes);

        /**
         * setter bubble factory for making text bubbles
         * @param fact layout factory
         */
        void setBubbleFact(const std::shared_ptr<LayoutFactory> &fact);

        /**
         * getter bubble factory to make text bubbles
         * @return  layout factory
         */
        const std::shared_ptr<LayoutFactory> &getBubbleFact() const;

        /**
         * getter is lock on shouting is true
         * @return bool
         */
        bool isShoutlock() const;

        /**
         * setter lock on shouting
         * @param shoutlock
         */
        void setShoutlock(bool shoutlock);

        /**
         * setter time when you can shout again
         * @param lockedtimer double time
         */
        void setShoutLockedtimer(double lockedtimer);

        /**
         * setter live score entity linked with this hiker
         * @param scoretext entity
         */
        void setScoretext(const std::shared_ptr<Entity> &scoretext);

        /**
         * getter live score entity
         * @return entity
         */
        const std::shared_ptr<Entity> &getScoretext() const;

    private:
        int allLaneCount = 0;
//    lock shout for a time so you cant keep shouting
        double shoutLockTimer = 0;
        bool shoutlock = false;
//    factory to make a speech bubble
        std::shared_ptr<LayoutFactory> bubbleFact = nullptr;
//    link the score to a hiker
        std::shared_ptr<Entity> scoretext = nullptr;
    };
}

#endif //TURBOHIKER_HIKER_H
