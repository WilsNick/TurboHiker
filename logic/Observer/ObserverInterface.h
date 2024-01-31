//
// Created by nick on 04.01.21.
//

#ifndef TURBOHIKER_OBSERVERINTERFACE_H
#define TURBOHIKER_OBSERVERINTERFACE_H

namespace turbohiker {
    /**
     * interface class for observer
     */
    class ObserverInterface {
    public:

        /**
         * destructor
         */
        virtual ~ObserverInterface() = default;

        /**
         * pure virtual function
         * @param s int: update the observer
         */
        virtual void update(int s) = 0;

        /**
         * get the score
         * @return int: score
         */
        virtual int getScore() = 0;
    };
}

#endif //TURBOHIKER_OBSERVERINTERFACE_H
