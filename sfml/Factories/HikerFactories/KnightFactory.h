//
// Created by nick on 31.12.20.
//

#ifndef TURBOHIKER_KNIGHTFACTORY_H
#define TURBOHIKER_KNIGHTFACTORY_H

#include "../../../logic/Factories/HikerFactory.h"
#include <SFML/Graphics.hpp>
#include "../../PassingSFML.h"

namespace turbohikerSFML {
    /**
     * derived class from Factory
     * Factory of knights
     */
    class KnightFactory : public turbohiker::HikerFactory {
    public:
        /**
         * constructor set sfml parts
         * @param w window
         * @param t texture
         * @param v view
         */
        KnightFactory(sf::RenderWindow &w, std::shared_ptr<sf::Texture> &t, sf::View &v);

        /**
         * create the knight
         * @param size Coordinates how big knight needs to be
         * @param position Coordinates where the hiker needs to be
         * @return Hiker
         */
        std::shared_ptr<turbohiker::Hiker>
        createHiker(turbohiker::Coordinates size, turbohiker::Coordinates position) override;

    private:
        sf::RenderWindow &window;
        sf::View &view;
        std::shared_ptr<sf::Texture> texture;
    };
}

#endif //TURBOHIKER_KNIGHTFACTORY_H
