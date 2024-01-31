//
// Created by nick on 02.01.21.
//

#ifndef TURBOHIKER_SPEECHBUBBLEFACTORY_H
#define TURBOHIKER_SPEECHBUBBLEFACTORY_H

#include "../../../logic/Factories/LayoutFactory.h"
#include "../../SpeechBubbleSFML.h"
#include <SFML/Graphics.hpp>

namespace turbohikerSFML {
    /**
     * derived class from LayoutFactory
     * Factory of speech bubbles
     */
    class SpeechBubbleFactory : public turbohiker::LayoutFactory {
    public:
        /**
         * constructor set sfml parts
         * @param w window
         * @param t texture
         * @param v view
         */
        SpeechBubbleFactory(sf::RenderWindow &w, std::shared_ptr<sf::Texture> &t, sf::View &v);

        /**
         *  create the bubble
         * @param size Coordinates how big bubble needs to be
         * @param position Coordinates where the entity needs to be
         * @return Entity
         */
        std::shared_ptr<turbohiker::Entity>
        createProp(turbohiker::Coordinates size, turbohiker::Coordinates position) override;

    private:
        sf::RenderWindow &window;
        sf::View &view;
        std::shared_ptr<sf::Texture> texture;
    };
}

#endif //TURBOHIKER_SPEECHBUBBLEFACTORY_H
