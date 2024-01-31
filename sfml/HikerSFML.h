//
// Created by nick on 27.12.20.
//

#ifndef TURBOHIKER_HIKERSFML_H
#define TURBOHIKER_HIKERSFML_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "../logic/Singletons/Transformation.h"

namespace turbohikerSFML {
    /**
     * SFML implement hiker functions that can be used by Player, Enemy, Passing
     */
    class HikerSFML {
    public:
        /**
         * Constructor
         * @param w reference to the window
         * @param tex  texture of hiker
         * @param size size of hiker
         * @param position list {x,y} coordinats
         * @param view refrence to the view
         */
        HikerSFML(sf::RenderWindow &w, const std::shared_ptr<sf::Texture> &tex, sf::Vector2f size,
                  sf::Vector2f position,
                  sf::View &v);

        /**
         * destructor
         */
        ~HikerSFML() = default;

        /**
         * draw on window
         */
        void render();

        /**
         * update the visuals of the text player
         * @param s coordinats
         * @param moved by y
         */
        void updateVisuals(turbohiker::Coordinates s, double y);;


    private:
        sf::RectangleShape body;
        sf::RenderWindow &window;
        sf::View &view;
    };
}

#endif //TURBOHIKER_HIKERSFML_H
