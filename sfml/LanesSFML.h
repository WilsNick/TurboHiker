//
// Created by nick on 28.12.20.
//

#ifndef TURBOHIKER_LANESSFML_H
#define TURBOHIKER_LANESSFML_H


#include "../logic/Layout.h"
#include <SFML/Graphics.hpp>

namespace turbohikerSFML {
    class LanesSFML : public turbohiker::Layout {
    public:
        /**
         * constructor
         * @param window reference to the window
         * @param col text color
         * @param size size of lane
         * @param position list {x,y} coordinats
         */
        LanesSFML(sf::RenderWindow &window, sf::Color col, sf::Vector2f size, sf::Vector2f position);

        /**
         * destructor
         */
        ~LanesSFML() override = default;

        /**
         * destructor
         */
        void render() override;

        /**
         * move text to view by x
         * @param m double
         */
        void moveToView(double m) override;

        /**
         * update the visuals of the text player
         * @param s coordinates
         */
        void updateVisuals(turbohiker::Coordinates s) override {};

        /**
         * setter toupdate
         * lines that divide lanes should move with the view but the enline does not
         * @param t bool
         */
        void setToupdate(bool t);

    private:
        sf::RectangleShape body;
        sf::RenderWindow &window;
//        lines that divide lanes should move with the view but the enline does not
        bool toupdate = false;
    };
}

#endif //TURBOHIKER_LANESSFML_H
