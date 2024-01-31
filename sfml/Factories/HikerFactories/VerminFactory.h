//
// Created by nick on 02.01.21.
//

#ifndef TURBOHIKER_VERMINFACTORY_H
#define TURBOHIKER_VERMINFACTORY_H

#include "../../../logic/Factories/HikerFactory.h"
#include <SFML/Graphics.hpp>
#include "../../PassingSFML.h"

namespace turbohikerSFML {
    /**
     * derived class from Factory
     * Factory of rats
     */
    class VerminFactory : public turbohiker::HikerFactory {
    public:
        /**
         * constructor set sfml parts
         * @param w window
         * @param t texture
         * @param v view
         */
        VerminFactory(sf::RenderWindow &w, std::shared_ptr<sf::Texture> &t, sf::View &v);

        /**
         * create the rat
         * @param size Coordinates how big rat needs to be
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

#endif //TURBOHIKER_VERMINFACTORY_H
