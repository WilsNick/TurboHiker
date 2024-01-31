//
// Created by nick on 04.01.21.
//

#ifndef TURBOHIKER_SUBJECTINTERFACE_H
#define TURBOHIKER_SUBJECTINTERFACE_H

#include "ObserverInterface.h"
#include <memory>
#include <vector>
#include <algorithm>

namespace turbohiker {
    /**
     * interface class for Subject: keeps observers
     */
    class SubjectInterface {
    public:
        /**
         * destructor
         */
        virtual ~SubjectInterface() = default;

        /**
         * pure virtual function
         * add an observer to the list
         * @param observer
         */
        virtual void registerObserver(std::shared_ptr<ObserverInterface> &observer) = 0;

        /**
         * pure virtual function
         * notify all the observers
         */
        virtual void notifyObservers() = 0;

        /**
         * set the score to al the observers
         * @param s the score that needs to be added
         */
        virtual void setScore(int s) = 0;

    };
}

#endif //TURBOHIKER_SUBJECTINTERFACE_H
