#pragma once
#include "Global.h"
#include "ActorTexture.h"
#include "ActorState.h"

class Actor
{
public:
	Actor() :
		position(0,0), speed(0,0), acceleration(0), lifetime(100),width(100),height(100),collision_uid(0)
	{
		uid = alloc_actor_uid();
	}
	~Actor() {}

	ActorState* current_state;
	int width;
	int height;

	Uint32 get_uid(void)			const   { return uid; }
	Uint32 get_collision_uid(void)	const   { return collision_uid.load(); }
	void set_collision_uid(Uint32 id)		{ collision_uid.store(id); }
	Uint32 get_fly_status(void)	const		{ return fly.load(); }
	void set_fly_status(Uint32 f)			{ fly.store(f); }
	void set_position(glm::vec2 p) {
		position = p;
		aabb.aa = p;
		aabb.bb.x = p.x + width;
		aabb.bb.y = p.y + height;
	}
	glm::vec2 get_position()		const	{ return position;}
	void set_speed(glm::vec2 s)					{ speed = s;}
	glm::vec2 get_speed(void)		const	{ return speed;}
	void set_acceleration(int acc)			{ acceleration.store(acc);}
	int get_acceleration(void)		const	{ return acceleration.load();}
	void set_lifetime(int life)				{ lifetime.store(life);}
	int get_lifetime(void)			const	{ return lifetime.load();}
	void update(void);
	void scroll_back(void);
	AABB_BOX get_aabb()				const   { return aabb;}

private:
    struct Trail{
		Trail(glm::vec2 pos, ActorState* ptr) { position = pos; state_ptr = ptr; }

        glm::vec2 position;
        ActorState* state_ptr;

    };
    std::deque<Trail> trails;

	Uint32 uid;
	MATERIAL material;
	glm::vec2 position;
	glm::vec2 speed;
	AABB_BOX aabb;

	std::atomic<Uint32> fly;
	std::atomic<Uint32> collision_uid;
	std::atomic<int> acceleration;
	std::atomic<int> lifetime;
};

