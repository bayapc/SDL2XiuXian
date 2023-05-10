#include "Player.h"
void Player::set_current_state(std::string name)
{
	//current_state = std::find(states.begin(),stats.end(),name);
	for (auto it = states.begin(); it != states.end(); it++)
	{
		if ((*it)->get_name() == name) {
			current_state = (*it);
		}
	}
}

std::string Player::get_current_state(void)
{
	return current_state->get_name();
}

void Player::update(void)
{
	glm::vec2 p = get_position();

	if (p.x < 0) {
		p.x = 0;
		set_position(p);
	}else if (p.x > GameWorld::screen_width -100) {
		p.x = GameWorld::screen_width -100;
		set_position(p);
	}
	if (p.y <= 220) {//low limit Stop
		p.y = 220;
		set_speed(glm::vec2(get_speed().x, 0));
		set_position(p);
	}

	if (get_acceleration()) {
		/* send move background event*/
		if ((p.x < GameWorld::screen_width / 3) || (p.x > GameWorld::screen_height / 2)) {
			EventManager* em = EventManager::get_instance();
			ActorEvent e;
			e.uid = em->get_uid_by_name("background");//background
			e.event = KEY_BACKGROUND_MOVE;
			e.speed = get_speed();
			em->dispatch_event(e);
		}
	}

	ActorEvent ae = EventManager::get_instance()->get_event(this);
	if (ae.uid != 0) {
		/* const speed in x axis direction*/
		set_acceleration(1);
		if (ae.event == KEY_DESTROY) {
			std::cout << "Player:Collision Event" << std::endl;
		}

		if (ae.event == KEY_WALK_RIGHT) {
			if (get_current_state() != "walk right") {
				set_current_state("walk right");
			}
			set_speed(glm::vec2(10,get_speed().y));
		}else if (ae.event == KEY_RUN_RIGHT) {
			if (get_current_state() != "walk right") {
				set_current_state("walk right");
			}
			set_speed(glm::vec2(25,get_speed().y));
		}else if (ae.event == KEY_WALK_LEFT) {
			if (get_current_state() != "walk left") {
				set_current_state("walk left");
			}
			set_speed(glm::vec2(-10,get_speed().y));
		}else if (ae.event == KEY_RUN_LEFT) {
			if (get_current_state() != "walk left") {
				set_current_state("walk left");
			}
			set_speed(glm::vec2(-25,get_speed().y));
		}else {
			if (ae.event == KEY_JUMP) {
				set_speed(glm::vec2(get_speed().x, 50));
			}else if (ae.event == KEY_RUN_JUMP) {
				set_speed(glm::vec2(get_speed().x, 100));
			}else if (ae.event == KEY_STOP) {
				/* decrease speed in x axis direction*/
				set_acceleration(0);
			}
			/* jump state need to be update*/
			if ((get_current_state() == "idle right") || (get_current_state() == "walk right")) {
				set_current_state("idle right");
			}
			else {
				set_current_state("idle left");
			}
		}
	}else {
		glm::vec2 speed = get_speed();
		if (speed.x == 0) {
			if ((get_current_state() == "idle right") || (get_current_state() == "walk right")) {
				set_current_state("idle right");
			}
			else {
				set_current_state("idle left");
			}
		}
	}

	Actor::update();
}
