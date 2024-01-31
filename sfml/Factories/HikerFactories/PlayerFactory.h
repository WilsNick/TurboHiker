//
// Created by nick on 28.12.20.
//

#ifndef TURBOHIKER_PLAYERFACTORY_H
#define TURBOHIKER_PLAYERFACTORY_H

#include "../../../logic/Factories/HikerFactory.h"
#include <SFML/Graphics.hpp>
#include "../../PlayerSFML.h"

namespace turbohikerSFML {
    /**
     * derived class from Factory
     * Factory of players
     */
    class PlayerFactory : public turbohiker::HikerFactory {
    public:
        /**
         * constructor set sfml parts
         * @param w window
         * @param t texture
         * @param v view
         * @param f factory for speech bubbles
         */
        PlayerFactory(sf::RenderWindow &w, std::shared_ptr<sf::Texture> &t, sf::View &v,
                      const std::shared_ptr<turbohiker::LayoutFactory> &f);

        /**
         * create the player
         * @param size Coordinates how big player needs to be
         * @param position Coordinates where the hiker needs to be
         * @return Hiker
         */
        std::shared_ptr<turbohiker::Hiker>
        createHiker(turbohiker::Coordinates size, turbohiker::Coordinates position) override;

    private:
        sf::RenderWindow &window;
        sf::View &view;
        std::shared_ptr<sf::Texture> texture;
//        factory for speech bubbles
        std::shared_ptr<turbohiker::LayoutFactory> fact = nullptr;
    };
}

#endif //TURBOHIKER_PLAYERFACTORY_H
