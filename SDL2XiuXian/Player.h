#pragma once
#include "Global.h"
#include "Actor.h"
#include "GameWorld.h"

class Player :public Actor
{
public:
    Player() :level(0), score(0) 
    {
        set_position(glm::vec2(50, 500));
    };
    ~Player() {};

    void set_current_state(std::string name);
    std::string get_current_state(void);
    void update(int v);
    //backpack;
    //weapon;
    Actor* addon;
    std::vector<ActorState *> states;
private:

    int level;
    int score;

};

