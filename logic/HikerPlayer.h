//
// Created by nick on 31.12.20.
//

#ifndef TURBOHIKER_HIKERPLAYER_H
#define TURBOHIKER_HIKERPLAYER_H


#include "Hiker.h"

namespace turbohiker {
    class HikerPlayer : public Hiker {
    public:
        /**
         * speed up entity
         * @param x integer: 1 if right, -1 if move left else 0
         * @param y integer: 1 if up, -1 if move down else 0
         */
        void speedup(int x, int y) override;

        /**
         * if there is no lock that creat a text bubble link it
         * @param start first lane
         * @param length lane length
         * @return entity: text bubble
         */
        std::shared_ptr<Entity> shout(double start, double length) override;

        /**
         * update the logic update coordinats
         * @return coordinates how much hiker is moved
         */
        Coordinates update() override;

        /**
         * remove the buff if enough time has passed
         */
        void removeBuff() override;
    };
}

#endif //TURBOHIKER_HIKERPLAYER_H
