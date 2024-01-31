//
// Created by nick on 04.01.21.
//

#ifndef TURBOHIKER_OBSERVER_H
#define TURBOHIKER_OBSERVER_H


#include "ObserverInterface.h"
#include "SubjectInterface.h"

namespace turbohiker {
    /**
     * Observer that implements the interface
     */
    class Observer : public ObserverInterface {
        double score = 0;
    public:

        /**
         * Initializer
         */
        Observer() = default;

        /**
         * update the score
         * @param s int: score to add
         */
        void update(int s) override;

        /**
         * getter score
         * @return int: score
         */
        int getScore() override;

    };
}

#endif //TURBOHIKER_OBSERVER_H
