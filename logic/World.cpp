//
// Created by nick on 27.12.20.
//

#include "World.h"

namespace turbohiker {

    World::~World() {
        while (!entityList.empty()) {
            remove(entityList.back());
        }
        if (player) {
            player = nullptr;
        }
    }

    void World::initGame(std::vector<std::shared_ptr<HikerFactory>> hikerFactorys,
                         std::vector<std::shared_ptr<LayoutFactory>> layoutFactorys,
                         int amount) {
//    calculate lane widht
        laneWidth = 8.0 / amount;
        double firstlanePos = -4 + laneWidth;
//    get player position
        std::shared_ptr<RandomeNumber> r = RandomeNumber::getInstance();
        int chance = r->getintpercent();
        int playerPosition = (int) ((chance * amount) / 100.0);

        playercount = amount - 1;
        firstPlayerPos = (firstlanePos - laneWidth / 2);

//    initialize layout en hikers
        for (int place = 0; place < amount; place++) {
//        place a lane line
            if (place < playercount) {
                addLaneLine(layoutFactorys[0], firstlanePos);
            }
//        add player en enemy hikers
            if (!player) {
                if (playerPosition == place) {
                    addPlayer(hikerFactorys[0], place);

                } else {
                    addEnemy(hikerFactorys[1], place);
                }
            } else {
                addEnemy(hikerFactorys[1], place);
            }
            firstlanePos += laneWidth;
        }
        addLayout(layoutFactorys);
    }

    void World::generateObstacle(std::vector<std::shared_ptr<HikerFactory>> f, int obstacleAmount) {
//    multiply the amount of obstacles with the lane amount
        obstacleAmount *= player->getAllLaneCount();
        std::shared_ptr<RandomeNumber> r = r->getInstance();
        int mistakes = 0;
        for (int i = 1; i < obstacleAmount; i++) {
//            when there are no more places to set the obstacles stop
            if(mistakes>300){break;}
//        randome choice between both factories
            int fact = r->getintpercent() % 2;
//        randome choice of y coordinates
            double randomeHeight = r->getRealNumber((int) tracklength - 3);
//        randome lane
            int randomeLane = r->getintpercent();
            int lane = randomeLane % (player->getAllLaneCount() + 1);
            std::shared_ptr<Hiker> hiker3;
            hiker3 = f[fact]->createHiker(Coordinates(laneWidth / 1.1 - 4, -2.5f),
                                          Coordinates(firstPlayerPos + laneWidth * lane, -3.0f - randomeHeight));
            hiker3->setAllLaneCount(player->getAllLaneCount());
            hiker3->setMyLane(lane);

            bool push = true;
//        if the obstacle is in collision with another generated obstacle -> redo this obstacle
            if (!obstacles.empty()) {
                for (const auto &o : obstacles) {
                    if (o != hiker3) {
                        if (Collider::CheckCollision(o, hiker3)) {
                            i--;
                            push = false;
                            mistakes++;
                        }
                    }
                }
            }
            if (push) {
                entityList.push_back(hiker3);
                obstacles.push_back(hiker3);
            }
        }
    }

    void World::removeTimeLock() {
        for (auto &entity : entityList) {
            if (entity->isTimeLocked() and entity->getTimeLock() < getTimer()) {
                entity->setTimeLocked(false);
            }
        }
    }

    void World::removeEntity() {
        std::vector<std::shared_ptr<Entity>> toremove = {};
        for (auto &entity: entityList) {
//        if entity has a text bubble check if this need to be removed
            if (entity->isHasTextBubble()) {
                std::shared_ptr<Entity> bubble = entity->removeShout(false);
                if (bubble) {
                    toremove.push_back(bubble);
                }
            }
//        if an entity goes above the finnish line it can be removed
            if (viewPos - entity->getPosition().y > tracklength) {
                if (entity->isEnemy()) {
                    placement++;
                    toremove.push_back(entity);
//            set player worldScore to the world
                } else if (entity == player) {
                    player->setScore(100 * playercount - 100 * placement);
                    worldScore = player->getScore();
                    toremove.push_back(player);
                    player = nullptr;
                } else if (entity->isObstacle()) {
                    toremove.push_back(entity);
                }
            }
        }
        while (!toremove.empty()) {
            remove(toremove.back());
            toremove.pop_back();
        }
    }

    void World::render() {
        player->getScoretext()->setScoreText(player->getScore());
        for (auto &obj: entityList) {
            obj->render();
        }
    }

    Coordinates World::update() {
        for (auto &obj : entityList) {
//        update the logic position
            Coordinates changedPos = obj->update();
            std::shared_ptr<Transformation> t = t->getInstance();
            Coordinates oldPos = t->logic_to_pixles(0, 0);
            Coordinates newPos = t->logic_to_pixles(changedPos.x * laneWidth, changedPos.y);
            Coordinates updatedPos = {oldPos.x - newPos.x, oldPos.y - newPos.y};
//        update the visual position
            obj->updateVisuals(updatedPos);
//        update the text bubble
            if (obj->isHasTextBubble()) {
                obj->getTextBubble()->setPosition(obj->getPosition().x, obj->getPosition().y - obj->getSize().y);
                obj->getTextBubble()->updateVisuals(updatedPos);
            }
        }
        return Coordinates{0, 0};
    }

    std::shared_ptr<Entity> World::shout(double shouted, double z) {
//    shouted will be 1 if player shouted else 0
        if (shouted == 1) {
            std::shared_ptr<Entity> o = player->shout(firstPlayerPos, laneWidth);
            if (o != nullptr) {
                player->setScore(-10);
                entityList.push_back(o);
                obstacleInLane(player, 5);
            }
        }
        for (auto &entity : entityList) {
            if (entity->isWantToShout()) {
                entity->setWantToShout(false);
                std::shared_ptr<Entity> obj = entity->shout(firstPlayerPos, laneWidth);
                if (obj != nullptr) {
                    entityList.push_back(obj);
                    obstacleInLane(entity, 5);
                }
            }
        }
        return nullptr;
    }

    void World::speedup(int speedv, int speedh) {
//    process input player
        speedh = speedupPlayer(speedh);
        for (auto &obj: entityList) {
            if (obj != player) {
//            generate input for enemies
                std::vector<int> speed = ai(obj);
                obj->speedup(speed[0], speed[1]);
            } else {
                obj->speedup(speedv, speedh);
            }
        }
    }

    void World::moveToView(double moved) {
        for (auto &obj: entityList) {
            obj->moveToView(moved);
        }
    }

    void World::Collision() {
        std::vector<double> moved = {0, 0};
        if (!entityList.empty()) {
            for (int i = 0; i < entityList.size() - 1; i++) {
                for (int j = i; j < entityList.size(); j++) {
                    if (i != j) {
//                    two objects shouldn't collide
                        if (!entityList[i]->isObstacle() or !entityList[j]->isObstacle()) {
//                        do collision detection
                            moved = Collider::CollisionDetection(entityList[i], entityList[j]);
//                        if there was a collision
                            if (moved[0] != 0 or moved[1] != 0) {
//                            if the player was in collision deduct worldScore
                                if (entityList[i] == player or entityList[j] == player) {
                                    player->setScore(-1);
                                }
//                            update visuals of collided entities
                                std::shared_ptr<Transformation> t = t->getInstance();
                                double oldp = t->logic_to_pixle_y(0);
                                double newp = t->logic_to_pixle_y(-moved[0]);
                                Coordinates updatep{0, oldp - newp};
                                double newp2 = t->logic_to_pixle_y(-moved[1]);
                                Coordinates updatep2{0, oldp - newp2};
                                entityList[i]->updateVisuals(updatep);
                                entityList[j]->updateVisuals(updatep2);
                            }
                        }
                    }
                }
            }
        }
    }

    void World::setTimers(double time, double delta) {
        setTimer(time);
        setDeltaTimer(delta);
        for (auto &entity : entityList) {
            entity->setDeltaTimer(delta);
            entity->setTimer(time);
        }
    }

    void World::removeBuff() {
        for (auto &e : entityList) {
            if (e->isBuffed()) {
                e->removeBuff();
            }
        }
    }

    double World::getPlayerPosy() {
        return player->getPosition().y;
    }

    double World::getPlayerSpeed() {
        return player->getSpeedv();
    }

    double World::getPlayerMaxSpeed() {
        return player->getMaxSpeed();
    }

    bool World::isPlayerBuffed() {
        return player->isBuffed();
    }

    void World::setTracklength(int t) {
        World::tracklength = t;
    }

    void World::setViewPos(double view) {
        World::viewPos = view;
    }

    bool World::isFinished() const {
        if (player == nullptr) {
            return true;
        }
        return false;
    }

    int World::getPlacement() const {
        return placement;
    }

    int World::getWorldScore() const {
        return worldScore;
    }

    void World::addLaneLine(const std::shared_ptr<LayoutFactory> &factory, double firstlanePos) {
        std::shared_ptr<Entity> entity = factory->createProp({-3.9f, 3.0f},
                                                             {firstlanePos, -3.0f});
        entityList.push_back(entity);
        entity->setMyLane(-1);
    }

    void World::addPlayer(const std::shared_ptr<HikerFactory> &factory, int place) {
        std::shared_ptr<Hiker> hiker = factory->createHiker(Coordinates{laneWidth / 1.1 - 4, -2.5f},
                                                            Coordinates{firstPlayerPos + laneWidth * place, 2.5f});
        hiker->setAllLaneCount(playercount);
        hiker->setMyLane(place);
        player = hiker;
        entityList.push_back(hiker);
    }

    void World::addEnemy(const std::shared_ptr<HikerFactory> &factory, int place) {
        std::shared_ptr<Hiker> hiker = factory->createHiker(Coordinates{laneWidth / 1.1 - 4, -2.5f},
                                                            Coordinates{firstPlayerPos + laneWidth * place, 2.5f});
        hiker->setAllLaneCount(playercount);
        hiker->setMyLane(place);
        entityList.push_back(hiker);
    }

    void World::addLayout(std::vector<std::shared_ptr<LayoutFactory>> factorys) {
        std::shared_ptr<Entity> endline = factorys[1]->createProp(Coordinates{4.0f, -2.9f},
                                                                  Coordinates{-4, -tracklength});
        std::shared_ptr<Entity> livescore = factorys[2]->createProp(Coordinates{-2.0f, -2.0f},
                                                                    Coordinates{7.5, -3.0f});
        std::shared_ptr<Entity> highScore = factorys[3]->createProp(Coordinates{-2.0f, -2.0f},
                                                                    Coordinates{7.5, -2.0f});

        entityList.push_back(endline);
        player->setScoretext(livescore);
        entityList.push_back(livescore);
        entityList.push_back(highScore);
    }

    void World::remove(std::shared_ptr<Entity> &toDel) {
//    if entity has a ballon but needs to be removed remove the bubble first
        if (toDel->isHasTextBubble()) {
            std::shared_ptr<Entity> bubble = toDel->removeShout(true);
            if (bubble) {
                removeHelper(bubble);
            }
        }
        toDel->deleteSubject();
        removeHelper(toDel);
    }

    void World::removeHelper(std::shared_ptr<Entity> &toDel) {
        entityList.erase(std::remove(entityList.begin(), entityList.end(), toDel), entityList.end());
        if (std::find(obstacles.begin(), obstacles.end(), toDel) != obstacles.end()) {

            obstacles.erase(std::remove(obstacles.begin(), obstacles.end(), toDel), obstacles.end());
        }
    }

    int World::speedupPlayer(int speedh) {
        int finalSpeedh = 0;
        if (speedh != 0) {
            bool left = (speedh < 0) ? true : false;
            bool canChangeLane = true;
            for (auto &entity : entityList) {
                if (entity != player) {
//                check if there is no object in the lane beside player
                    if (not Collider::checklaneswitch(player, entity, left)) {
                        canChangeLane = false;
                    }
//                check if player is not in collision (can not move if iin collision)
                    if (Collider::CheckCollision(player, entity)) {
                        canChangeLane = false;
                    }
                }
            }
//        timeLock so you cant switch allLaneCount to quickly
            if (not player->isTimeLocked() and canChangeLane) {
                finalSpeedh = speedh;
                player->setTimeLock(getTimer() + 200000);
                player->setTimeLocked(true);
            }
        }
        return finalSpeedh;
    }

    void World::obstacleInLane(const std::shared_ptr<Entity> &e, int distance) {
        for (auto &o : obstacles) {
            if (e->getMyLane() == o->getMyLane()) {
                if (e->getPosition().y > o->getPosition().y and e->getPosition().y - distance < o->getPosition().y) {
                    o->shout(0, 0);
                }
            }

        }
    }

    std::vector<int> World::ai(const std::shared_ptr<Entity> &entity) {
//    v will be 1 if ther is an obstacle in front of it else 0
//    h 3 if obstacle left and right, 2 if obstacle left, 1 if obstacle right else 0
        int v = 0;
        int h = 0;

        if (checkClosesdObstacleInLane(entity, 3)) {
            v = 1;
        }
        std::vector<bool> horizontal = checkLaneSwitch(entity);
        if (!horizontal[0] and !horizontal[1]) {
            h = 3;
        } else if (horizontal[0]) {
            h = 2;
        } else if (horizontal[1]) {
            h = 1;
        }
        return {v, h};
    }

    bool World::checkClosesdObstacleInLane(const std::shared_ptr<Entity> &hiker, int distance) {
        for (auto &o : obstacles) {
//        check if obstacle is in the same name as the hiker
            if (hiker->getMyLane() == o->getMyLane()) {
//            check if the hiker is close enough
                if (hiker->getPosition().y > o->getPosition().y and
                    hiker->getPosition().y - distance < o->getPosition().y) {
                    return true;
                }
            }
        }
        return false;
    }

    std::vector<bool> World::checkLaneSwitch(const std::shared_ptr<Entity> &e) {
        bool leftSide = true;
        bool rightSide = true;
        for (auto &entity : entityList) {
            if (entity != e) {
//            check if hiker can move left
                if (not Collider::checklaneswitch(e, entity, true) or e->getMyLane() == 0) {
                    leftSide = false;
                }
//            check if hiker can move right
                if (not Collider::checklaneswitch(e, entity, false) or e->getMyLane() == playercount) {
                    rightSide = false;
                }
            }
        }
        return {leftSide, rightSide};
    }
}