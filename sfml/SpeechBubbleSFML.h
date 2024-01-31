//
// Created by nick on 02.01.21.
//

#ifndef TURBOHIKER_SPEECHBUBBLESFML_H
#define TURBOHIKER_SPEECHBUBBLESFML_H

#include <SFML/Graphics.hpp>
#include "../logic/Layout.h"

namespace turbohikerSFML {
    class SpeechBubbleSFML : public turbohiker::Layout {
    public:
        /**
         * Constructor
         * @param window reference to the window
         * @param tex  texture of bubble
         * @param size size of bubble
         * @param position list {x,y} coordinats
         * @param view refrence to the view
         */
        SpeechBubbleSFML(sf::RenderWindow &w, const std::shared_ptr<sf::Texture> &tex, sf::Vector2f size,
                         sf::Vector2f position, sf::View &v);

        /**
         * draw on window
         */
        void render() override;

        /**
         * update the visuals of the text bubble
         * @param s
         */
        void updateVisuals(turbohiker::Coordinates s) override;

        /**
         * NOOP
         * @param s double
         */
        void moveToView(double s) override {};

    private:
        sf::RectangleShape body;
        sf::RenderWindow &window;
        sf::View &view;
    };
}

#endif //TURBOHIKER_SPEECHBUBBLESFML_H
