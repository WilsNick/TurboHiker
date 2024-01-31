//
// Created by nick on 31.12.20.
//

#ifndef TURBOHIKER_HIKERPASSING_H
#define TURBOHIKER_HIKERPASSING_H


#include "Hiker.h"

namespace turbohiker {
    /**
     * Passing hiker (obstacle) derived from hiker
     */
    class HikerPassing : public Hiker {
    public:
        /**
         * If a player shouts at this obstacle  it will do an action by chance
         * @param x unused
         * @param y unused
         * @return nullpointer
         */
        std::shared_ptr<Entity> shout(double x, double y) override;

        /**
         * update obstacle horizontal if knight, vertical if rat
         * @return coordinates how much obstacle is moved
         */
        Coordinates update() override;

        /**
         * see if the buff of the rat needs to be removed
         */
        void removeBuff() override;

        /**
         * set if the obstacle is a knight
         * @param h bool true if knight, false if rat
         */
        void setKnight(bool h);

        /**
         * NOOP
         */
        void speedup(int, int) override {};

    private:
//    knight if true else Rat
        bool knight = false;
    };
}

#endif //TURBOHIKER_HIKERPASSING_H
