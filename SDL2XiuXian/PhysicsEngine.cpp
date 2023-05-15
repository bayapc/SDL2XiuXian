#include "PhysicsEngine.h"

void PhysicsEngine::calculate_position(Actor* a,FLOAT t)
{
	glm::vec2 speed = a->get_speed();
	//std::cout << "PhyEngine:speed:(" << speed.x << "," << speed.y << ")" << std::endl;
	glm::vec2 pos = a->get_position();
	pos.x = pos.x + speed.x * t;
	pos.y = pos.y + speed.y * t - 0.5 * 9.8 * t * t;//invert y coordinate
	a->set_position(pos);

	if (a->get_uid() == 2) {
		/* update map global x offset */
		GameWorld::map_offset_x += speed.x * t * 0.5;
		if (GameWorld::map_offset_x > 3000) {
			GameWorld::map_offset_x = 3000;
		}
		if (GameWorld::map_offset_x < 0) {
			GameWorld::map_offset_x = 0;
		}

		//std::cout << "plyer: speed(" << speed.x << "," << speed.y <<")"<< std::endl;
	}

#if true
	/* acceleration feature */
	if (a->get_acceleration() == 0) {
		/* from other state to idle,start decrease speed.x */
		if (speed.x > 1) {
			speed.x = speed.x - t;
		}else if (speed.x < -1) {
			speed.x = speed.x + t;
		}else {
			speed.x = 0;
		}
	}
#endif
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
		if (a->get_collision_uid()) {
			if (a->get_collision_uid() == (*i)->get_uid()) {
				if (is_collision(a->get_aabb(), (*i)->get_aabb())) {
				}else {
					/* Clean collision flag,prepare for a new collision*/
					a->set_collision_uid(0);
					(*i)->set_collision_uid(0);
				}
				break;
			}
			continue;
		}
		if ((*i)->get_lifetime() == 0) {
			continue;
		}
		if ((*i)->get_collision_uid()) {
			continue;
		}
		if (is_collision(a->get_aabb(),(*i)->get_aabb())) {
			ActorEvent e;
			e.uid = a->get_uid();
			e.event = KEY_DESTROY;
			em->dispatch_event(e);
			(*i)->set_collision_uid(e.uid);//ignore multi collision
			//std::cout << "a co_id:" << e.uid <<"aa.y:"<<a->get_aabb().aa.y<<"bb.y"<< a->get_aabb().bb.y<<"pos("<<a->get_position().x<<"," << a->get_position().y<< std::endl;
			if ((*i)->get_lifetime() > 0) {
				e.uid = (*i)->get_uid();
				em->dispatch_event(e);
				a->set_collision_uid(e.uid);//ignore multi collision
				//std::cout << "b co_id:" << e.uid << "aa.y:" << (*i)->get_aabb().aa.y << "bb.y" << (*i)->get_aabb().bb.y << "pos(" << (*i)->get_position().x << "," << (*i)->get_position().y << std::endl;
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
				if ((*i)->get_lifetime() == 0) {
					continue;
				}
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
