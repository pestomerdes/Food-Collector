/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include "game.h"
using namespace std;


// Constructors
Game::Game(){ }

Game::Game(int height, int width){
    this->height = height;
    this->width  = width;
    newGame();
}

// Getters
int Game::getHeight(){ return height; }

int Game::getWidth(){ return width; }

void Game::draw(){
    vector<vector<Cell *> > m = map.getMap();
    for (int i = 0; i < map.getHeigth(); i++)
        for (int j = 0; j < map.getWidth(); j++)
            m[i][j]->draw();

    player.draw();
    enemy.draw();
    // std::cout << "Score: " << player.getScore() << " " << enemy.getScore() << std::endl;
}

void Game::newGame(){
    newMap();
    player = Agent(PLAYER, map.initPlayer(), new Strategy(map));
    enemy  = Agent(ENEMY, map.initEnemy(), new ReflexAgent(map));
    player.setAgent(&enemy);
    enemy.setAgent(&player);
    map.print();
}

void Game::integrate(long t){
    integrate(&player, t);
    integrate(&enemy, t);
}

void Game::integrate(Agent * agent, long t){
    if (agent->integrate(t) || agent->getState() == QUIET) {
        agent->setPosition(agent->getNextPosition());
        Direction d = agent->getStrategy()->getAction(agent->getCurrentPosition());
        agent->setNextDirection(d);
        agent->tryNextDirection();
        agent->move();
    }
}

void Game::moveAgent(CellType cellType, Direction direction){
    if (cellType == PLAYER) {
        if (player.getState() == QUIET) {
            player.setDirection(direction);
            player.move();
        } else {
            player.setNextDirection(direction);
        }
    } else if (cellType == ENEMY) {
        enemy.setNextDirection(direction);
    }
}

void Game::newMap(){
    map = Map(height, width);
}
