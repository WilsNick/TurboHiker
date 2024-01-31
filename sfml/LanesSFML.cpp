//
// Created by nick on 28.12.20.
//

#include "LanesSFML.h"

namespace turbohikerSFML {
    LanesSFML::LanesSFML(sf::RenderWindow &w, sf::Color col, sf::Vector2f size, sf::Vector2f position)
            : window(w) {

        body.setSize(size);
        body.setFillColor(col);
        body.setPosition(position);
    }

    void LanesSFML::render() {
        window.draw(body);
    }

    void LanesSFML::moveToView(double moved) {
        if (toupdate) {
            std::shared_ptr<turbohiker::Transformation> t = t->getInstance();
            int oldp = t->logic_to_pixle_y(0);
            int newp = t->logic_to_pixle_y(moved);
            float updatep = (float) newp - (float) oldp;
            body.move(0, updatep);
        }
    }

    void LanesSFML::setToupdate(bool t) {
        toupdate = t;
    }
}