//
// Created by nick on 30.12.20.
//

#ifndef TURBOHIKER_RANDOMENUMBER_H
#define TURBOHIKER_RANDOMENUMBER_H

#include <random>
#include <iostream>
#include <cstdlib>
#include <memory>

namespace turbohiker {
    /**
     * Singleton
     * generate random numbers
     */
    class RandomeNumber {
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<> distrib;
//        instance of class
        static std::shared_ptr<RandomeNumber> instance;

        /**
         * Private constructor so that no objects can be created
         */
        RandomeNumber() {
//        seed random
            std::mt19937 gen2(rd());
            gen = gen2;
            std::uniform_int_distribution<int> distrib2(1, 100);
            distrib = distrib2;
        };

    public:
        /**
         * Get instance from the class
         * if the instance is not initialized -> initialize
         * @return instance
         */
        static std::shared_ptr<RandomeNumber> getInstance() {
            if (!instance) {
                instance.reset(new RandomeNumber());
            }
            return instance;
        }

        /**
         * get random number between 1 and 100
         * @return int random number
         */
        int getintpercent() { return distrib(gen); };

        /**
         * generate randome number between 1 and maxInt
         * @param maxInt int: max number
         * @return double max int
         */
        double getRealNumber(int maxInt) {
            std::uniform_real_distribution<double> distrib3(1, maxInt);
            return distrib3(gen);
        };
    };
}

#endif //TURBOHIKER_RANDOMENUMBER_H
