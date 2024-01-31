//
// Created by nick on 31.12.20.
//

#ifndef TURBOHIKER_ENEMYFACTORY_H
#define TURBOHIKER_ENEMYFACTORY_H


#include "../../../logic/Factories/HikerFactory.h"
#include <SFML/Graphics.hpp>
#include "../../EnemySFML.h"

namespace turbohikerSFML {
    /**
     * derived class from Factory
     * Factory of enemies
     */
    class EnemyFactory : public turbohiker::HikerFactory {
    public:
        /**
         * constructor set sfml parts
         * @param w window
         * @param t texture
         * @param v view
         * @param f factory for speech bubbles
         */
        EnemyFactory(sf::RenderWindow &w, std::shared_ptr<sf::Texture> &t, sf::View &v,
                     const std::shared_ptr<turbohiker::LayoutFactory> &f);

        /**
         * create the enemy
         * @param size Coordinates how big enemy needs to be
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

#endif //TURBOHIKER_ENEMYFACTORY_H
