#pragma once
#include "Global.h"
#include "ActorTexture.h"
#include "ActorState.h"

class Actor
{
public:
	Actor() :
		x(0), y(0), speed(0), acceleration(0), lifetime(100)
	{
	}
	~Actor() {}
	void set_position(glm::vec2 p)			{ x = static_cast<unsigned int>(p.x); y = static_cast<unsigned int>(p.y);}
	glm::vec2 get_position()		const	{ return glm::vec2(x, y);}
	void set_speed(int s)					{ speed = s;}
	int get_speed(void)				const	{ return speed;}
	void set_acceleration(int acc)			{ acceleration = acc;}
	int get_acceleration(void)		const	{ return acceleration;}
	void set_lifetime(int life)				{ lifetime = life;}
	int get_lifetime(void)			const	{ return lifetime;}
	void update(void)						{ if (current_state != NULL) { current_state->update(); } }

	ActorState* current_state;
private:
	unsigned int x;
	unsigned int y;
	int speed;
	int acceleration;
	int lifetime;
};

