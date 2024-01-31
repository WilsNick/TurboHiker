//
// Created by nick on 31.12.20.
//

#ifndef TURBOHIKER_HIKERENEMY_H
#define TURBOHIKER_HIKERENEMY_H


#include "Hiker.h"

namespace turbohiker {
    /**
     * Enemy hiker derived from hiker
     */
    class HikerEnemy : public Hiker {
    public:
        /**
         * speed up entity alsways trying to go faster, moves left if needed by a chance
         * @param x integer: 1 if obstacle in front else 0
         * @param y integer: speedh 3 if obstacle left and right, 2 if obstacle left, 1 if obstacle right else 0
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

#endif //TURBOHIKER_HIKERENEMY_H
