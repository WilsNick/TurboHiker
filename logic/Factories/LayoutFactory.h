//
// Created by nick on 02.01.21.
//

#ifndef TURBOHIKER_LAYOUTFACTORY_H
#define TURBOHIKER_LAYOUTFACTORY_H

#include <memory>
#include <vector>
#include "../Entity.h"
#include "../Singletons/Transformation.h"

namespace turbohiker {
    /**
     * base interface class for layout factories
     */
    class LayoutFactory {
    public:
        /**
         * pure virtal function
         * create a layout element
         * @param size coordinates how big the entity needs to be
         * @param position coordinates where the entity needs to be
         * @return
         */
        virtual std::shared_ptr<Entity> createProp(Coordinates size, Coordinates position) = 0;
    };
}

#endif //TURBOHIKER_LAYOUTFACTORY_H
