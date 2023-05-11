#include "PhysicsEngine.h"

void PhysicsEngine::calculate_position(Actor* a,FLOAT t)
{
	glm::vec2 speed = a->get_speed();
	//std::cout << "PhyEngine:speed:(" << speed.x << "," << speed.y << ")" << std::endl;
	glm::vec2 pos = a->get_position();
	pos.x = pos.x + speed.x * t;
	pos.y = pos.y + speed.y * t - 0.5 * 9.8 * t * t;//invert y coordinate
	a->set_position(pos);

	if (a->get_acceleration() == 0) {
		/* from other state to idle,start decrease speed.x */
		if (speed.x > 0.2) {
			speed.x = speed.x - t;
		}
		else if (speed.x < -0.2) {
			speed.x = speed.x + t;
		}
		else {
			speed.x = 0;
		}
	}
	speed.y = speed.y - 9.8 * t;
	a->set_speed(speed);
	//if (speed.y != 0) {
		//std::cout << "T:" << t << std::endl;
		//std::cout << "PhyEngine:pos:(" << pos.x << "," << pos.y << ")" << std::endl;
		//std::cout << "PhyEngine:pos:(" << pos.x << "," << pos.y << ") speed:(" << speed.x << "," << speed.y << ")" << std::endl;
	//}
}

static bool is_collision(AABB_BOX first, AABB_BOX second)
{
	bool collisionX = (first.bb.x >= second.aa.x) && (first.aa.x <= second.bb.x);
	bool collisionY = (first.bb.y >= second.aa.y) && (first.aa.y <= second.bb.y);

	return collisionX && collisionY;
}

void PhysicsEngine::do_collision(Actor* a)
{
	EventManager* em = EventManager::get_instance();
	for (auto i = GameWorld::Get_Instance()->visible_list.begin(); i != GameWorld::Get_Instance()->visible_list.end(); i++) {
		if (a->get_uid() == (*i)->get_uid()) {
			continue;
		}
		if (is_collision(a->get_aabb(),(*i)->get_aabb())) {
			ActorEvent e;
			e.uid = a->get_uid();
			e.event = KEY_DESTROY;
			em->dispatch_event(e);
			std::cout << "a co_id:" << e.uid << std::endl;
			if ((*i)->get_lifetime() > 0) {
				e.uid = (*i)->get_uid();
				em->dispatch_event(e);
				std::cout << "b co_id:" << e.uid << std::endl;
			}
			break;
		}
	}
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
				do_collision(*i);
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
