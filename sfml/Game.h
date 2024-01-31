//
// Created by nick on 27.12.20.
//

#ifndef TURBOHIKER_GAME_H
#define TURBOHIKER_GAME_H

#include <memory>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../logic/Singletons/Transformation.h"
#include "../logic/Singletons/RandomeNumber.h"
#include "../logic/Entity.h"
#include "../logic/World.h"
#include "HikerSFML.h"
#include "Factories/HikerFactories/PlayerFactory.h"
#include "Factories/HikerFactories/EnemyFactory.h"
#include "Factories/HikerFactories/KnightFactory.h"
#include "Factories/LayoutFactories/LineFactory.h"
#include "Factories/HikerFactories/VerminFactory.h"
#include "Factories/LayoutFactories/SpeechBubbleFactory.h"
#include "Factories/LayoutFactories/ScoreFactory.h"

namespace turbohikerSFML {
    /**
     * Run the game loop
     */
    class Game {
    public:
        /**
         * constructor game
         */
        Game();

        /**
         * destructor game
         */
        ~Game();

        /**
         * run the game loop
         * @return boolean: true if you want to restart game
         */
        bool run();

    private:
        /**
         * handle window events like close and resize
         */
        void handleEvent();

        /**
         * initializes game by sending to helper functions
         */
        void init();

        /**
         * initializes background
         */
        void initBackground();

        /**
         * initialize hikers and lines
         */
        void initStartPosition();

        /**
         * initialize obstacles
         */
        void initObstacles();

        /**
         * get input from player
         * first is 1 if up, -1 if down
         * second is 1 if right, -1 if down
         * thirt is 1 if space
         * @return vector of integers
         */
        static std::vector<int> getInput();

        /**
         * get input from user for endloop
         * @return boolean: true if r is pressed
         */
        static bool restartInput();

        double moveView();

        /**
         * calculate how much the view needs to be adjusted
         * @return where the player can be on screen
         */
        int calculateViewAdjustment();

        /**
         * draw the background image
         */
        void drawBackground();

        /**
         * end gameloop
         * @param placement: int placement of player
         * @param score : int score of the player
         */
        void endLoop(int placement, int score);

        /**
         * get the end text and highscore text for the endloop
         * @param placement: int placement of player
         * @param score : int score of the player
         * @return vector of texts
         */
        std::vector<sf::Text> getScoreScreen(int placement, int score);

        /**
         * write top 10 highscores from a file
         */
        void writeHighscore();

        /**
         * get the highscores from a file
         */
        void getHighscores();

    private:
        std::shared_ptr<turbohiker::Transformation> t;
        std::shared_ptr<turbohiker::RandomeNumber> r;

        std::shared_ptr<turbohiker::World> world;

        sf::RenderWindow window;
        sf::View view;
//        keep the textures and fonts
        std::vector<std::shared_ptr<sf::Texture>> textures = {};
        std::vector<sf::Sprite> backgrounds = {};
        std::vector<std::shared_ptr<sf::Font>> fonts = {};
//        how many players
        int playercount = 0;
//        highscores
        std::vector<int> scores;
//        if true restart the game
        bool restartGame = false;
    };
}

#endif //TURBOHIKER_GAME_H
