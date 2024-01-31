//
// Created by nick on 30.12.20.
//

#ifndef TURBOHIKER_COLLIDER_H
#define TURBOHIKER_COLLIDER_H


#include <memory>
#include "Hiker.h"

namespace turbohiker {
    /**
     * checks collisions and handles them
     */
    class Collider {
    public:
        /**
         * constructor
         */
        explicit Collider() = default;

        /**
         * destructor
         */
        ~Collider() = default;

        /**
         * do collision detection
         * move entities away from eachother if needed
         * add buffs if needed
         * @param first entity 1
         * @param other entity 2
         * @return list of doubles : how much each entity is moved, {first, other}
         */
        static std::vector<double>
        CollisionDetection(std::shared_ptr<Entity> &first, std::shared_ptr<Entity> &other);

        /**
         * checks if other is in the wey to move left or right
         * @param first entity 1
         * @param other entity 2
         * @return bool true is to check left
         */
        static bool
        checklaneswitch(const std::shared_ptr<Entity> &first, const std::shared_ptr<Entity> &other, bool left);

        /**
         * Check is 2 entities are in collision
         * @param first entity 1
         * @param other entity 2
         * @return bool true if in collision
         */
        static bool CheckCollision(const std::shared_ptr<Entity> &first, const std::shared_ptr<Entity> &other);
    };
}

#endif //TURBOHIKER_COLLIDER_H
