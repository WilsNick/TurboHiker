#include "sfml/Game.h"

int main() {
    bool runGame = true;
    while (runGame) {
        turbohikerSFML::Game game;
//        returns true if the player wants to restart the game
        runGame = game.run();
    }
    return 0;
}