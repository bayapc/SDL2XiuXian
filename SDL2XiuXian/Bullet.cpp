#include "Bullet.h"

void Bullet::set_current_state(std::string name)
{
	//current_state = std::find(states.begin(),stats.end(),name);
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
	//std::cout << "bullet:s(" << s.y << ")"<< std::endl;

	if (p.x < 0) {
		p.x = 0;
		set_speed(glm::vec2(-s.x,s.y));
		set_position(p);
	}else if (p.x > GameWorld::screen_width -100) {
		p.x = GameWorld::screen_width -100;
		set_position(p);
		set_speed(glm::vec2(-s.x,s.y));
	}
	if (p.y < 50) {//low limit Stop
		p.y = 50;
		//set_speed(glm::vec2(s.x,100));
		if (abs(s.y) < 10) {
			s.y = 0;
		}
		if (abs(s.x) < 1) {
			s.x = 0;
		}
		set_speed(glm::vec2(s.x,-s.y*0.9));
		set_position(p);
	}else if (p.y > GameWorld::screen_height) {
		p.y = GameWorld::screen_height;
		set_speed(glm::vec2(s.x, 0));
		set_position(p);
	}

	ActorEvent ae = EventManager::get_instance()->get_event(this);
	if (ae.uid != 0) {
		//std::cout << "Bullet(" << ae.uid << "):Collision Event" << std::endl;
		/* const speed in x axis direction*/
		//set_acceleration(1);
		if (ae.event == KEY_DESTROY) {
			//std::cout << "Bullet(" <<ae.uid<<"):Collision Event" << std::endl;
			if (get_current_state() != "final") {
				set_current_state("final");
			}else {
				set_current_state("normal");
			}
			set_speed(glm::vec2(s.x, -s.y * 0.9));
			set_position(p);
		}
	}

	Actor::update();
}

