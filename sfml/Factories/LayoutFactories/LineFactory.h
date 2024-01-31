//
// Created by nick on 28.12.20.
//

#ifndef TURBOHIKER_LINEFACTORY_H
#define TURBOHIKER_LINEFACTORY_H

#include "../../../logic/Factories/LayoutFactory.h"
#include "../../LanesSFML.h"
#include <SFML/Graphics.hpp>

namespace turbohikerSFML {
    /**
     * derived class from LayoutFactory
     * Factory of lines
     */
    class LineFactory : public turbohiker::LayoutFactory {
    public:
        /**
         * constructor set sfml parts
         * @param w window
         * @param col color of the line
         * @param v view
         * @param m bool if line needs to be moved with the view
         */
        LineFactory(sf::RenderWindow &w, sf::Color col, sf::View &v, bool m);

        /**
         *  create the line
         * @param size Coordinates how big line needs to be
         * @param position Coordinates where the entity needs to be
         * @return Entity
         */
        std::shared_ptr<turbohiker::Entity>
        createProp(turbohiker::Coordinates size, turbohiker::Coordinates position) override;

    private:
        sf::RenderWindow &window;
        sf::View &view;
        const sf::Color color;
        bool movable;
    };
}

#endif //TURBOHIKER_LINEFACTORY_H
