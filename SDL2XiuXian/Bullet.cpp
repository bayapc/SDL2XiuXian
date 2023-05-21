#include "Bullet.h"

void Bullet::set_current_state(std::string name)
{
	for (auto it = states.begin(); it != states.end(); it++)
	{
		if ((*it)->get_name() == name) {
			current_state = (*it);
		}
	}
}

std::string Bullet::get_current_state(void)
{
	return current_state->get_name();
}

void Bullet::update(void)
{
	glm::vec2 p = get_position();
	glm::vec2 s = get_speed();

	if (p.x < (0+GameWorld::map_offset_x)) {
		p.x = (0+GameWorld::map_offset_x);
		set_speed(glm::vec2(-s.x,s.y));
		set_position(p);
	}else if (p.x > (GameWorld::screen_width + GameWorld::map_offset_x)) {
		p.x = (GameWorld::screen_width + GameWorld::map_offset_x);
		set_position(p);
		set_speed(glm::vec2(-s.x,s.y));
	}
	if (p.y < 50) {//low limit Stop
		p.y = 50;
		if (abs(s.y) < 10) {
			s.y = 0;
		}
		if (abs(s.x) < 1) {
			s.x = 0;
		}
		set_speed(glm::vec2(s.x,-s.y*0.8));
		set_position(p);
	}else if (p.y > GameWorld::screen_height) {
		p.y = GameWorld::screen_height;
		set_speed(glm::vec2(s.x, 0));
		set_position(p);
	}

	ActorEvent ae = EventManager::get_instance()->get_event(this);
	if (ae.uid != 0) {
		/* const speed in x axis direction*/
		if (ae.event == KEY_DESTROY) {
			//std::cout << "Bullet(" <<ae.uid<<"):Collision Event" << std::endl;
			set_current_state("final");
			set_lifetime(0);
			set_speed(glm::vec2(s.x, -s.y * 0.8));
			set_position(p);
		}
	}

	Actor::update();
}

