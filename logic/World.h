//
// Created by nick on 27.12.20.
//

#ifndef TURBOHIKER_WORLD_H
#define TURBOHIKER_WORLD_H


#include "Entity.h"
#include "Factories/HikerFactory.h"
#include "Factories/LayoutFactory.h"
#include "Collider.h"

namespace turbohiker {
    /**
     * the world of the game: sends all the entities
     */
    class World : public Entity {
    public:
        /**
         * constructor
         */
        World() = default;

        /**
         * destructor
         */
        ~World() override;

        /**
         * initialize the hikers and lanes
         * @param hikerFactorys list of factories: {player, enemy}
         * @param layoutFactorys list of factories: {laneline, endline, livescore, highscore}
         * @param amount: integer how many lanes
         */
        void
        initGame(std::vector<std::shared_ptr<HikerFactory>> hikerFactorys,
                 std::vector<std::shared_ptr<LayoutFactory>> layoutFactorys, int amount);

        /**
         * generate obstacles
         * @param f: list of obstacle factories {knight, rat}
         * @param amount: int amount of obstacleper lane
         */
        void generateObstacle(std::vector<std::shared_ptr<HikerFactory>> f, int amount);

        /**
         * remove entities
         */
        void removeEntity();

        /**
         * remove the timelock of all entities
         */
        void removeTimeLock();

        /**
         * render all entities
         */
        void render() override;

        /**
         * update all entities
         * @return Coordinats not needed
         */
        Coordinates update() override;

        /**
         * if hikers wants to yell-> shout
         * @return Entity the text bubble
         */
        std::shared_ptr<Entity> shout(double, double) override;

        /**
         * speedup all entities
         * @param speedv integer: 1 if up, -1 if down else 0
         * @param speedh integer: 1 if right, -1 if left else 0
         */
        void speedup(int speedv, int speedh) override;

        /**
         * move all entities to the view update
         * @param moved : double how much the view is moved
         */
        void moveToView(double moved) override;

        /**
         * check collision detection for all entities
         */
        void Collision();

        /**
         * set the timer  and delta timer for all entities
         * @param timer double time
         * @param delta double time per round
         */
        void setTimers(double timer, double delta);

        /**
         * remove the buff on all entities
         */
        void removeBuff() override;

        /**
         * get the y position of the player
         * @return double y position
         */
        double getPlayerPosy();

        /**
         * ge tspeed of a player
         * @return double player speed
         */
        double getPlayerSpeed();

        /**
         * get maximum speed of the player
         * @return double max speed
         */
        double getPlayerMaxSpeed();

        /**
         * check is the player is buffed
         * @return true is player is buffed
         */
        bool isPlayerBuffed();

        /**
         * setter for tracklength
         * @param tracklength integer
         */
        void setTracklength(int tracklength);

        /**
         * setter vieuw position
         * @param view double
         */
        void setViewPos(double view);

        /**
         * check if player is finished
         * @return true is player is finished
         */
        bool isFinished() const;

        /**
         * getter placement of player
         * @return integer
         */
        int getPlacement() const;

        /**
         * getter of the world score
         * @return integer
         */
        int getWorldScore() const;

        /**
         * NOOP
         * @param force bool
         * @return nullpointer
         */
        std::shared_ptr<Entity> removeShout(bool force) override { return nullptr; };

    private:
        /**
         * make a line
         * @param factory line factory
         * @param firstlanePos double x position
         */
        void addLaneLine(const std::shared_ptr<LayoutFactory> &factory, double firstlanePos);

        /**
         * make a player
         * @param factory player factory
         * @param place int placement
         */
        void addPlayer(const std::shared_ptr<HikerFactory> &factory, int place);

        /**
         * make an enemy
         * @param factory enemy factory
         * @param place int placement
         */
        void addEnemy(const std::shared_ptr<HikerFactory> &factory, int place);

        /**
         * make score, highscore and endline
         * @param factorys list of factories {endline, score, highscore}
         */
        void addLayout(std::vector<std::shared_ptr<LayoutFactory>> factorys);

        /**
         * remove an entitie
         * @param toDel entity to remove
         */
        void remove(std::shared_ptr<Entity> &toDel);

        /**
         * helper to remove
         * @param toDel entity to remove
         */
        void removeHelper(std::shared_ptr<Entity> &toDel);

        /**
         * NOOP
         * @param s coordinats
         */
        void updateVisuals(Coordinates s) override {};

        /**
         * check if the player can switch lanes
         * @param speedh : integer 1 if right, -1 if left else 0
         * @return integer
         */
        int speedupPlayer(int speedh);

        /**
         * generate speedup for enemies
         * @param entity get speedup for this entity
         * @return list of integers
         */
        std::vector<int> ai(const std::shared_ptr<Entity> &entity);

        /**
         * shout at an obstacle in the same lane which is max distance away
         * @param e entity
         * @param distance integer
         */
        void obstacleInLane(const std::shared_ptr<Entity> &e, int distance);

        /**
         * check is obstacle is in the same lane and distance away from entitie
         * @param hiker entity to check
         * @param distance integer
         * @return true if obstacle in lane in distance
         */
        bool checkClosesdObstacleInLane(const std::shared_ptr<Entity> &hiker, int distance);

        /**
         * check is you can switch lanes for enemy ai
         * @param e entity
         * @return list of booleans {left, right}, true if can move
         */
        std::vector<bool> checkLaneSwitch(const std::shared_ptr<Entity> &e);

    private:
        //List of all hikers of the world
        std::vector<std::shared_ptr<Entity>> entityList = {};
        //List of all obstacles of the world
        std::vector<std::shared_ptr<Entity>> obstacles = {};

        std::shared_ptr<Hiker> player = nullptr;
        int worldScore = 0;
        int placement = 0;
        int playercount = 0;
        double laneWidth = 0;
        double tracklength = 86;
        double firstPlayerPos = 0;
        double viewPos = 0;
    };

}
#endif //TURBOHIKER_WORLD_H
