#include "PhysicsEngine.h"

void PhysicsEngine::calculate_position(Actor* a,FLOAT t)
{
	glm::vec2 speed = a->get_speed();
	glm::vec2 pos = a->get_position();
	pos.x = pos.x + speed.x * t;
	pos.y = pos.y + speed.y * t - 0.5 * 9.8 * t * t;//invert y coordinate
	a->set_position(pos);

	if (speed.x > 0) {
		speed.x = speed.x - t;
	}else {
		speed.x = 0;
	}
	speed.y = speed.y - 9.8 * t;
	a->set_speed(speed);
	//if (speed.y != 0) {
		//std::cout << "T:" << t << std::endl;
		std::cout << "PE:pos:(" << pos.x << "," << pos.y << ")" << std::endl;
		//std::cout << "PE:pos:(" << pos.x << "," << pos.y << ") speed:(" << speed.x << "," << speed.y << ")" << std::endl;
	//}
}

void PhysicsEngine::engine_thread(void)
{
	Uint32 interval = 0;//ms
	Uint32 oldTime = SDL_GetTicks();
	Uint32 newTime = SDL_GetTicks();

	for (;;)
	{
		newTime = SDL_GetTicks();
		interval = newTime-oldTime;

		if( interval > 16) { //60fps
			if(list.empty()) {
				continue;
			}
			for (auto i = list.begin(); i != list.end(); i++) {
				calculate_position(*i,interval*0.01);
			}
			oldTime = newTime;
		}
		//Sleep(1);
	}
}

PhysicsEngine::PhysicsEngine()
{
	mThread = std::thread(&PhysicsEngine::engine_thread, this);
	mThread.detach();
}

PhysicsEngine::~PhysicsEngine()
{
	mThread.~thread();
}

void PhysicsEngine::OnStart(void)
{
}
