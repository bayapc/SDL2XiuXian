#pragma once
#include "Global.h"
#include "Actor.h"
#include "GameWorld.h"
#include "EventManager.h"

class Bullet :
    public Actor
{
public:
    Bullet() :hurt_value(10), hurt_radio(100) 
    {
        set_position(glm::vec2(350, 550));
        set_speed(glm::vec2(0,0));
        /* width and height should automatically loading from current picture*/
        width = 32;
        height = 32;
    };
    ~Bullet() {};

    void set_current_state(std::string name);
    std::string get_current_state(void);
    void update();
    std::vector<ActorState *> states;
private:
    int hurt_value;
    int hurt_radio;
};

