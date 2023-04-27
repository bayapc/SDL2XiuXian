#pragma once
#include "Global.h"
#include "ActorTexture.h"
#include "ActorState.h"

class Actor
{
public:
	Actor() :
		position(0,0), speed(0,0), acceleration(0), lifetime(100)
	{
		uid = alloc_actor_uid();
	}
	~Actor() {}
	Uint32 get_uid(void)			const   { return uid; }
	void set_position(glm::vec2 p)			{ position = p; }
	glm::vec2 get_position()		const	{ return position;}
	void set_speed(glm::vec2 s)					{ speed = s;}
	glm::vec2 get_speed(void)		const	{ return speed;}
	void set_acceleration(int acc)			{ acceleration = acc;}
	int get_acceleration(void)		const	{ return acceleration;}
	void set_lifetime(int life)				{ lifetime = life;}
	int get_lifetime(void)			const	{ return lifetime;}
	void update(void);
	void scroll_back(void);

	ActorState* current_state;
private:
    struct Trail{
		Trail(glm::vec2 pos, ActorState* ptr) { position = pos; state_ptr = ptr; }

        glm::vec2 position;
        ActorState* state_ptr;

    };
    std::deque<Trail> trails;

	Uint32 uid;
	glm::vec2 position;
	glm::vec2 speed;
	int acceleration;
	int lifetime;
};

