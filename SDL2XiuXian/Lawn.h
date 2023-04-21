#pragma once
#include "Global.h"
#include "Actor.h"
class Lawn :
    public Actor
{
public:
    Lawn() {
        set_position(glm::vec2(0,550));
    }
    ~Lawn() {};
    void set_current_state(std::string name);
    std::string get_current_state(void);
    std::vector<ActorState *> states;
};

