//
// Created by nick on 02.01.21.
//

#ifndef TURBOHIKER_LAYOUT_H
#define TURBOHIKER_LAYOUT_H


#include "Entity.h"

namespace turbohiker {
    /**
     * Handle the NOOP from layout entities like score or lines
     */
    class Layout : public Entity {
    public:
        /**
         * destructor
         */
        ~Layout() override = default;

        /**
         * NOOP
         * @return Coordinats :{0,0}
         */
        Coordinates update() override { return {0, 0}; };

        /**
         * NOOP
         * @param i int
         * @param i1 int
         */
        void speedup(int i, int i1) override {};

        /**
         * NOOP
         * @param x double
         * @param e double
         * @return nullpointer
         */
        std::shared_ptr<Entity> shout(double x, double e) override { return nullptr; };

        /**
         * NOOP
         * @param force bool
         * @return nullpointer
         */
        std::shared_ptr<Entity> removeShout(bool force) override { return nullptr; };

        /**
         * NOOP
         */
        void removeBuff() override {};
    };
}

#endif //TURBOHIKER_LAYOUT_H
