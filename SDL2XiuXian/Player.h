#pragma once
#include "Global.h"
#include "Actor.h"
class Player :public Actor
{
public:
    Player() :level(0), score(0) 
    {
        memset(posion_record, 0, 1000);
    };
    ~Player() {};

    void set_current_state(std::string name);
    std::string get_current_state(void);
    //backpack;
    //weapon;
    Actor* addon;
    std::vector<ActorState *> states;
private:
    int level;
    int score;
    glm::vec2 posion_record[1000];

};

