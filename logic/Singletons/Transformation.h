//
// Created by nick on 28.12.20.
//

#ifndef TURBOHIKER_TRANSFORMATION_H
#define TURBOHIKER_TRANSFORMATION_H

#include <iostream>
#include <tuple>
#include <memory>
#include "../Coordinates.h"

namespace turbohiker {
    /**
     * Singleton
     * Transorm pixles to logic and the other way
     * logic is x[-4, 4], y[-3, 3]
     */
    class Transformation {
//        instance of the class
        static std::shared_ptr<Transformation> instance;
//        initialize size window on 100x100
        int window_x = 100;
        int window_y = 100;

        /**
         * Private constructor so that no objects can be created
         */
        Transformation() = default;

    public:
        /**
         * Get instance from the class
         * if the instance is not initialized -> initialize
         * @return instance
         */
        static std::shared_ptr<Transformation> getInstance() {
            if (!instance) {
                instance.reset(new Transformation());
            }
            return instance;
        }

        /**
         * transform logic to pixles
         * @param x double
         * @param y double
         * @return pixle coordinates
         */
        Coordinates logic_to_pixles(double x, double y) const;

        /**
         * transform logic to pixle for y
         * @param y double
         * @return integer pixle
         */
        int logic_to_pixle_y(double y) const;

        /**
         * transform pixle to logic for y
         * @param y double
         * @return double logic
         */
        double pixle_to_logic_y(double y) const;

        /**
         * set window width and length
         * @param x int width
         * @param y int length
         */
        void changeWindow(const int x, const int y) {
            window_x = x;
            window_y = y;
        }
    };
}
#endif //TURBOHIKER_TRANSFORMATION_H
