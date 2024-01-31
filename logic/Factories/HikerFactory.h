//
// Created by nick on 28.12.20.
//

#ifndef TURBOHIKER_HIKERFACTORY_H
#define TURBOHIKER_HIKERFACTORY_H

#include <memory>
#include <vector>
#include "../Singletons/Transformation.h"
#include "../Hiker.h"

namespace turbohiker {
    /**
     * base interface class for hiker factories
     */
    class HikerFactory {
    public:
        /**
         * pure virtual function
         * create a hiker
         * @param size coordinates how big the entity needs to be
         * @param position coordinates where the entity needs to be
         * @return
         */
        virtual std::shared_ptr<Hiker> createHiker(Coordinates size, Coordinates position) = 0;
    };
}

#endif //TURBOHIKER_HIKERFACTORY_H
