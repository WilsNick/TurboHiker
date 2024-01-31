//
// Created by nick on 31.12.20.
//

#include "EnemySFML.h"

namespace turbohikerSFML {
    EnemySFML::EnemySFML(sf::RenderWindow &w, const std::shared_ptr<sf::Texture> &tex, sf::Vector2f size,
                         sf::Vector2f position, sf::View &v)
            : sfml(std::make_shared<HikerSFML>(w, tex, size, position, v)) {


    }

    void EnemySFML::updateVisuals(turbohiker::Coordinates s) {
        sfml->updateVisuals(s, getPosition().y);
    }
}
