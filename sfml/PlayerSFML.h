//
// Created by nick on 31.12.20.
//

#ifndef TURBOHIKER_PLAYERSFML_H
#define TURBOHIKER_PLAYERSFML_H


#include "../logic/HikerPlayer.h"
#include "HikerSFML.h"

namespace turbohikerSFML {
    /**
     * SFML implementation of a player
     */
    class PlayerSFML : public turbohiker::HikerPlayer {
    public:
        /**
         * Constructor
         * @param w reference to the window
         * @param tex  texture of player
         * @param size size of player
         * @param position list {x,y} coordinats
         * @param view refrence to the view
         */
        PlayerSFML(sf::RenderWindow &w, const std::shared_ptr<sf::Texture> &tex, sf::Vector2f size,
                   sf::Vector2f position,
                   sf::View &v);

        /**
         * draw on window
         */
        void render() override { sfml->render(); };

        /**
         * update the visuals of the text player
         * @param s coordinates
         */
        void updateVisuals(turbohiker::Coordinates s) override;

    private:
//        use HikerSFML to handle these functions
        std::shared_ptr<HikerSFML> sfml;
    };
}

#endif //TURBOHIKER_PLAYERSFML_H
