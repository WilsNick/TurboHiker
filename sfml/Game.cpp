//
// Created by nick on 27.12.20.
//

#include "Game.h"

namespace turbohikerSFML {
    Game::Game()
            : window(sf::VideoMode(1088, 600), "Turbohiker", sf::Style::Close | sf::Style::Resize),
              view(window.getDefaultView()) {
        view.move(-300, 0);
        world = std::make_shared<turbohiker::World>();
        r = turbohiker::RandomeNumber::getInstance();
        t = turbohiker::Transformation::getInstance();
        t->changeWindow(380, 600);
        double d = t->pixle_to_logic_y(-8000);
        world->setTracklength((int) -d);
    }

    Game::~Game() {
        while (!textures.empty()) {
            textures.pop_back();
        }
        while (!backgrounds.empty()) {
            backgrounds.pop_back();
        }
        while (!fonts.empty()) {
            fonts.pop_back();
        }
    };

    bool Game::run() {

        std::clock_t startTime = std::clock();
        init();
        //Main loop of the game
        int placement = 0;
        int score = 0;
        while (window.isOpen()) {
//        set the view in world
            double viewPos = t->pixle_to_logic_y(view.getCenter().y);
            world->setViewPos(-viewPos);
//        if you are faster then 60 frames per sec wait
            std::clock_t beginRound = startTime;
            startTime = std::clock();
            double delta = (double) startTime - beginRound;
            startTime = std::clock();

//        set input to 60 Frames per sec
            world->setTimers(beginRound, delta / 20000.0);
//        timeLock is for moving playercount
            world->removeTimeLock();
//        input player verical speed, knight speed, yell
            std::vector<int> input = getInput();
//        handle input and generate/handle input for ai
            world->speedup(input[0], input[1]);
            world->shout(input[2], 0);
//        clear speedbuff/buffed if needed
            world->removeBuff();

            window.clear();
            world->update();
//        remove enemies and player if they finish
            world->removeEntity();
            bool finished = world->isFinished();
//        you have isFinished
            if (finished) {
                placement = world->getPlacement();
                score = world->getWorldScore();
                scores.push_back(score);
                break;
            }
//        check on collision
            world->Collision();
//        move view with player
            double moved = moveView();
            world->moveToView(moved);
            window.setView(view);
//        draw
            drawBackground();
            world->render();
            window.display();

            //Handle window events
            handleEvent();
        }
        if (window.isOpen()) {
            endLoop(placement + 1, score);
        }
        return restartGame;

    }

    void Game::handleEvent() {
        sf::Event evnt{};
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    break;
                default:
                    break;

            }
        }
    }

    void Game::init() {
        getHighscores();
        initBackground();
        initStartPosition();
        initObstacles();
    }

    void Game::initBackground() {
        std::shared_ptr<sf::Texture> backgroundTex = std::make_shared<sf::Texture>();
        backgroundTex->loadFromFile("./res/map.png");
        textures.push_back(backgroundTex);

        sf::Sprite background(*backgroundTex);
        backgrounds.push_back(background);
        backgrounds[0].setPosition(-300, 600);


        sf::Sprite background2(*backgroundTex);
        backgrounds.push_back(background2);
        backgrounds[1].setPosition(-300, 0);

        sf::Sprite background3(*backgroundTex);
        backgrounds.push_back(background3);
        backgrounds[2].setPosition(-300, -600);
    }

    void Game::initStartPosition() {
//    make a speech bubble factory for the hikers sow they can yell
        std::shared_ptr<sf::Texture> SpeechBubbleTexture = std::make_shared<sf::Texture>();
        SpeechBubbleTexture->loadFromFile("./res/textbubble.png");
        textures.push_back(SpeechBubbleTexture);
        std::shared_ptr<SpeechBubbleFactory> speechBubble = std::make_shared<SpeechBubbleFactory>(window,
                                                                                                  SpeechBubbleTexture,
                                                                                                  view);


        std::shared_ptr<sf::Texture> playerTexture = std::make_shared<sf::Texture>();
        playerTexture->loadFromFile("./res/player.png");
        textures.push_back(playerTexture);
        std::shared_ptr<PlayerFactory> player = std::make_shared<PlayerFactory>(window, playerTexture, view,
                                                                                speechBubble);

        std::shared_ptr<sf::Texture> enemyTexture = std::make_shared<sf::Texture>();
        enemyTexture->loadFromFile("./res/enemy.png");
        textures.push_back(enemyTexture);
        std::shared_ptr<EnemyFactory> enemy = std::make_shared<EnemyFactory>(window, enemyTexture, view,
                                                                             speechBubble);

        std::vector<std::shared_ptr<turbohiker::HikerFactory>> hikers;
        hikers.push_back(player);
        hikers.push_back(enemy);

        std::shared_ptr<sf::Font> f = std::make_shared<sf::Font>();
        if (!f->loadFromFile("./res/Hardigan.otf")) {
            std::cout << "error loading file" << std::endl;
            system("pause");
        }
        fonts.push_back(f);
//    get highscore in text
        std::string higscoretext = "Highscores:\n";
        int y = 0;
        for (auto score : scores) {
            y++;
            higscoretext += std::to_string(score) + "\n";
            if (y == 10) {
                break;
            }
        }

//    layout factory
        std::vector<std::shared_ptr<turbohiker::LayoutFactory>> layout;
        std::shared_ptr<turbohiker::LayoutFactory> laneLine = std::make_shared<LineFactory>(
                LineFactory(window, sf::Color::White, view, true));
        std::shared_ptr<turbohiker::LayoutFactory> endlLine = std::make_shared<LineFactory>(
                LineFactory(window, sf::Color::White, view, false));
        std::shared_ptr<turbohiker::LayoutFactory> liveScore = std::make_shared<ScoreFactory>(window, sf::Color::White,
                                                                                              view,
                                                                                              "Score:\n", f, true);
        std::shared_ptr<turbohiker::LayoutFactory> highScore = std::make_shared<ScoreFactory>(window, sf::Color::White,
                                                                                              view,
                                                                                              higscoretext, f, false);
        layout.push_back(laneLine);
        layout.push_back(endlLine);
        layout.push_back(liveScore);
        layout.push_back(highScore);

//    amount of playercount
        int chance = r->getintpercent();
        chance = (int) ((chance * 3.0) / 100.0);
        playercount = chance + 4;


        world->initGame(hikers, layout, chance + 4);
    }

    void Game::initObstacles() {
        std::shared_ptr<sf::Texture> knightTexture = std::make_shared<sf::Texture>();
        knightTexture->loadFromFile("./res/knight.png");
        textures.push_back(knightTexture);

        std::shared_ptr<sf::Texture> ratTexture = std::make_shared<sf::Texture>();
        ratTexture->loadFromFile("./res/rat.png");
        textures.push_back(ratTexture);

        std::shared_ptr<turbohiker::HikerFactory> knight = std::make_shared<KnightFactory>(window, knightTexture, view);
        std::shared_ptr<turbohiker::HikerFactory> rat = std::make_shared<VerminFactory>(window, ratTexture, view);
        int amountPerLane = 25;
        world->generateObstacle({knight, rat}, amountPerLane);
    }

    std::vector<int> Game::getInput() {
        int speedv = 0;
        bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        if (up) {
            speedv++;
        }
        if (down) {
            speedv--;
        }

        int speedh = 0;
        bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        if (right) {
            speedh++;
        }
        if (left) {
            speedh--;
        }

        int spaceinput = 0;
        bool space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (space) {
            spaceinput++;
        }
        return {speedv, speedh, spaceinput};
    }

    bool Game::restartInput() {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    }

    double Game::moveView() {
        double posy = world->getPlayerPosy();
        int viewPosy = t->logic_to_pixle_y(posy);
//    for the beginning if the view did not move yet and the position of player low enough don't move the view
        if (view.getCenter().y == 100 and posy > 2) {
            return 0;
        }
        double speed = world->getPlayerSpeed();
        double adjustment = calculateViewAdjustment();
//    only move the view if the speed is greater then 0 and the player above the place where it may be
        if (speed >= 0) {
            if (viewPosy < adjustment) {
                view.move(0, (float) (viewPosy - adjustment));
//            calulate how much is moved
                double speedy = t->pixle_to_logic_y(viewPosy);
                double newpospixley = t->pixle_to_logic_y(adjustment);
                double adjustmentcalc = speedy - newpospixley;
                return adjustmentcalc;
            }
        }
        return 0;
    }

    int Game::calculateViewAdjustment() {
        double speed = world->getPlayerSpeed();
        double maxspeed = world->getPlayerMaxSpeed();
//    if the player is debuffed then it can his max speed is reduced by half
        if (world->isPlayerBuffed()) {
            maxspeed *= 2;
        }
//    scaling formula
        double scaledspeed = (speed + maxspeed) / (maxspeed * 2);
//    scale to the logic coordinates
        scaledspeed *= 3;
        scaledspeed -= 1.5;
//    800 is the place where player will be when he doesnt move
        int beforhalf = 800 - t->logic_to_pixle_y(scaledspeed);
        return beforhalf;
    }

    void Game::drawBackground() {
//    move backgrounds in blocks
        double v = view.getCenter().y;
        if (v - (view.getSize().y / 2.0) < backgrounds[1].getPosition().y) {
            backgrounds[0].move(0, -600);
            backgrounds[1].move(0, -600);
            backgrounds[2].move(0, -600);
        } else if (v - (view.getSize().y / 2.0) > backgrounds[0].getPosition().y) {
            backgrounds[0].move(0, 600);
            backgrounds[1].move(0, 600);
            backgrounds[2].move(0, 600);
        }
//    draw background
        window.draw(backgrounds[0]);
        window.draw(backgrounds[1]);
        window.draw(backgrounds[2]);
    }

    void Game::endLoop(int placement, int score) {
        std::vector<sf::Text> victorytext = getScoreScreen(placement, score);
        writeHighscore();
        view.setCenter(300, 300);
        window.setView(view);
        while (window.isOpen()) {
            drawBackground();
            window.draw(victorytext[0]);
            window.draw(victorytext[1]);
            window.display();
            handleEvent();
            if (restartInput()) {
                restartGame = true;
                break;
            }
        }
    }

    std::vector<sf::Text> Game::getScoreScreen(int placement, int score) {
//    middel screen text
        std::string printing =
                "You finnished:\n" + std::to_string(placement) + " / " + std::to_string(playercount) + "\n";
        printing += "With a worldScore of:\n" + std::to_string(score) + "\n";
        printing += "To restart game:\n Press 'R'";
        sf::Text victorytext;
        victorytext.setFont(*fonts[0]);
        victorytext.setCharacterSize(35);
        victorytext.setFillColor(sf::Color::Black);
        victorytext.setPosition(0, 100);
        victorytext.setString(printing);

//    update highscores
        sort(scores.begin(), scores.end());
        std::reverse(scores.begin(), scores.end());
        std::string higscoretext = "Highscores:\n";
        int y = 0;
        for (auto highscore : scores) {
            y++;
            higscoretext += std::to_string(highscore) + "\n";
            if (y == 10) {
                break;
            }
        }
//    updated highscore
        sf::Text highscoretext;
        highscoretext.setString(higscoretext);
        highscoretext.setFillColor(sf::Color::White);
        highscoretext.setPosition(600, 100);
        highscoretext.setFont(*fonts[0]);
        highscoretext.setCharacterSize(35);
        std::vector<sf::Text> texts;
        texts.push_back(victorytext);
        texts.push_back(highscoretext);
        return texts;
    }

    void Game::writeHighscore() {
        std::ofstream myfile;
        myfile.open("./res/worldScore.txt");
        int y = 0;
        for (auto score : scores) {
            y++;
            myfile << std::to_string(score) << std::endl;
            if (y == 10) {
                break;
            }
        }
        myfile.close();

    }

    void Game::getHighscores() {
        std::string myText;
        std::ifstream myfile("./res/worldScore.txt");
        if (myfile.is_open()) {
            while (getline(myfile, myText)) {

                try {
                    int x = std::stoi(myText);
                    scores.push_back(x);

                }
                catch (std::exception &err) {
                    std::cout << "Corrupted highscore" << std::endl;
                }
            }
            std::sort(scores.begin(), scores.end());
            std::reverse(scores.begin(), scores.end());
        }
    }
}