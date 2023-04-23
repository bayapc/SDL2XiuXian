#pragma once
#include "Global.h"
#include "Actor.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void OnStart(void);

	std::vector<Actor*> list;
	void calculate_position(Actor* a,FLOAT t);
private:
	void engine_thread(void);
	std::thread mThread;
};

