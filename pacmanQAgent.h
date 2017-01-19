#ifndef PACMAN_Q_AGENT
#define PACMAN_Q_AGENT

#include <map>
#include <string>
#include "strategy.h"
#include "map.h"
#include "enums.h"
class PacmanQAgent : public Strategy {
public:
    PacmanQAgent();
    PacmanQAgent(Map * gameState, float epsilon = 5, float alpha = 0.2, float discount = 0.9);
    float getQValue(Map state, Direction action);
    float computeValueFromQValues(Map state);
    Direction computeActionFromQValues(Map state);
    Direction getAction(Map state);
    bool flipCoin(float epsilon);
    void doAction(Map state, Direction action);
    void update(Map state, Direction action, Map nextState, float reward);
    Direction getPolicy(Map state);
    float getValue(Map state);
    /************** Start ReinforcementAgent **************/
    void observeTransition(Map state, Direction action, Map nextState, float deltaReward);
    Map observationFunction(Map state);
    void final(Map state);
    /************** End ReinforcementAgent **************/
protected:
    CellType agent;
    float epsilon;
    float alpha;
    float discount;
    map<string, float> qValues;
    Map lastState;
    bool lastStateOk;
    Direction lastAction;
private:
    string getKey(Map state, Direction action);
    Direction argMax(map<Direction, float> values);
};
#endif // ifndef Q_LEARNING_AGENT