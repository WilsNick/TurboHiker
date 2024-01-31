//
// Created by nick on 28.12.20.
//

#include "LineFactory.h"

namespace turbohikerSFML {
    LineFactory::LineFactory(sf::RenderWindow &w, const sf::Color col, sf::View &v, bool m)
            : view(v), window(w), color(col), movable(m) {

    }

    std::shared_ptr<turbohiker::Entity>
    LineFactory::createProp(turbohiker::Coordinates size, turbohiker::Coordinates position) {
        std::shared_ptr<turbohiker::Transformation> t = t->getInstance();
        turbohiker::Coordinates s = t->logic_to_pixles(size.x, size.y);
        sf::Vector2f sfmlsize = sf::Vector2f(static_cast<float>(s.x), static_cast<float>(s.y));

        turbohiker::Coordinates p = t->logic_to_pixles(position.x, position.y);
        sf::Vector2f sfmlposition = sf::Vector2f(static_cast<float>(p.x), static_cast<float>(p.y));

        std::shared_ptr<LanesSFML> entity = std::make_shared<LanesSFML>(
                LanesSFML(window, color, sfmlsize, sfmlposition));
        entity->setToupdate(movable);
        return entity;
    }
}
