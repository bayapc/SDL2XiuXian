#pragma once
#include "Global.h"
#include "Actor.h"
#include "GameWorld.h"
#include "EventManager.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void OnStart(void);

	std::vector<Actor*> list;
	void calculate_position(Actor* a,FLOAT t);
	void do_collision(Actor* a);
private:
	void engine_thread(void);
	std::thread mThread;
};

