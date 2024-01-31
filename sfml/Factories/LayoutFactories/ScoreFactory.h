//
// Created by nick on 04.01.21.
//

#ifndef TURBOHIKER_SCOREFACTORY_H
#define TURBOHIKER_SCOREFACTORY_H

#include "../../../logic/Factories/LayoutFactory.h"
#include "../../TextFieldSFML.h"
#include <SFML/Graphics.hpp>

namespace turbohikerSFML {
    /**
     * derived class from LayoutFactory
     * Factory of speech score
     */
    class ScoreFactory : public turbohiker::LayoutFactory {
    public:
        /**
         * constructor set sfml parts
         * @param w window
         * @param col collor of the text
         * @param v view
         * @param s string
         * @param f font of the text
         * @param t bool if text is live or not
         */
        ScoreFactory(sf::RenderWindow &w, sf::Color col, sf::View &v, std::string s, std::shared_ptr<sf::Font> &f,
                     bool t);

        /**
         *  create the score
         * @param size not needed
         * @param position Coordinates where the entity needs to be
         * @return Entity
         */
        std::shared_ptr<turbohiker::Entity>
        createProp(turbohiker::Coordinates size, turbohiker::Coordinates position) override;


    private:
        sf::RenderWindow &window;
        sf::View &view;
        const sf::Color color;
        std::string text;
        std::shared_ptr<sf::Font> font;
        bool toupdate = false;

    };
}

#endif //TURBOHIKER_SCOREFACTORY_H
