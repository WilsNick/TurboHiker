//
// Created by nick on 04.01.21.
//

#ifndef TURBOHIKER_TEXTFIELDSFML_H
#define TURBOHIKER_TEXTFIELDSFML_H

#include "../logic/Layout.h"
#include <SFML/Graphics.hpp>

namespace turbohikerSFML {
    /**
     * Score text entity
     */
    class TextFieldSFML : public turbohiker::Layout {
    public:
        /**
         * constructor
         * @param window reference to the window
         * @param col text color
         * @param position list {x,y} coordinats
         * @param s string text
         * @param f pointer to a font
         * @param t bool if text needs to be live updated
         */
        TextFieldSFML(sf::RenderWindow &window, sf::Color col, sf::Vector2f position, const std::string &s,
                      const std::shared_ptr<sf::Font> &f, bool t);

        /**
         * destructor
         */
        ~TextFieldSFML() override = default;

        /**
         * draw on window
         */
        void render() override;

        /**
         * move text to view by x
         * @param x double
         */
        void moveToView(double x) override;

        /**
         * NOOP
         * @param s Coordinates
         */
        void updateVisuals(turbohiker::Coordinates s) override {};

    private:
        sf::Text body;
        sf::RenderWindow &window;
        std::string text;
//    highscore should not be update but live score should
        bool toupdate = true;
    };
}

#endif //TURBOHIKER_TEXTFIELDSFML_H
