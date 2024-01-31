//
// Created by nick on 04.01.21.
//

#include "TextFieldSFML.h"

namespace turbohikerSFML {
    TextFieldSFML::TextFieldSFML(sf::RenderWindow &w, sf::Color col, sf::Vector2f position, const std::string &s,
                                 const std::shared_ptr<sf::Font> &f, bool u)
            : window(w) {
        text = s;
        body.setFont(*f);
        body.setString(s);
        body.setCharacterSize(30);
        body.setFillColor(col);
        body.setPosition(position);
        toupdate = u;
    }

    void TextFieldSFML::render() {
        if (toupdate) {
            body.setString(text + getScoreText());
        }
        window.draw(body);
    }

    void TextFieldSFML::moveToView(double moved) {
        std::shared_ptr<turbohiker::Transformation> t = t->getInstance();
        int oldp = t->logic_to_pixle_y(0);
        int newp = t->logic_to_pixle_y(moved);
        auto updatep = (float) (newp - oldp);
        body.move(0, updatep);
    }
}