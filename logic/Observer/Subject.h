//
// Created by nick on 04.01.21.
//

#ifndef TURBOHIKER_SUBJECT_H
#define TURBOHIKER_SUBJECT_H

#include "SubjectInterface.h"
#include "ObserverInterface.h"

namespace turbohiker {
    /**
     * A concrete implementation of the SubjectInterface interface
     */
    class Subject : public SubjectInterface {
        int value = 0;
//        list of observers
        std::vector<std::shared_ptr<ObserverInterface>> observers;
    public:

        /**
         * destructor
         */
        ~Subject() override;

        /**
         * add an observer to the list
         * @param observer
         */
        void registerObserver(std::shared_ptr<ObserverInterface> &observer) override;

        /**
         * pure virtual function
         * notify all the observers
         */
        void notifyObservers() override;

        /**
         * set the score to al the observers
         * @param s the score that needs to be added
         */
        void setScore(int s) override;
    };
}

#endif //TURBOHIKER_SUBJECT_H
