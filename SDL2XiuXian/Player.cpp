#include "Player.h"
void Player::set_current_state(std::string name)
{
	//current_state = std::find(states.begin(),stats.end(),name);
	for (auto it = states.begin(); it != states.end(); it++)
	{
		if ((*it)->get_name() == name) {
			current_state = (*it);
			SDL_QueryTexture(current_state->get_current_picture()->get_texture(),NULL,NULL,&width,&height);
			width = width * 3;
			height = height * 3;
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

	if (p.x < (0+GameWorld::map_offset_x)) {
		p.x = (0+GameWorld::map_offset_x);
		set_position(p);
	}else if (p.x > (GameWorld::screen_width -100 + GameWorld::map_offset_x)) {
		p.x = (GameWorld::screen_width -100 + GameWorld::map_offset_x);
		set_position(p);
	}

	if (p.y < 60) {//low limit Stop
		p.y = 60;
		set_speed(glm::vec2(get_speed().x, 0));
		set_position(p);
	}

	if (get_acceleration()) {
		/* send move background event*/
		//if ((p.x < (GameWorld::map_offset_x + GameWorld::screen_width / 3)) || (p.x > (GameWorld::map_offset_x + GameWorld::screen_height / 2))) {
			EventManager* em = EventManager::get_instance();
			ActorEvent e;
			e.uid = em->get_uid_by_name("background");//background
			e.event = KEY_BACKGROUND_MOVE;
			e.speed = get_speed();
			e.speed.x = e.speed.x / 2;
			em->dispatch_event(e);
			//std::cout << "Player:Send Event to background" << std::endl;
		//}
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
			set_speed(glm::vec2(20,get_speed().y));
		}else if (ae.event == KEY_RUN_RIGHT) {
			if (get_current_state() != "walk right") {
				set_current_state("walk right");
			}
			set_speed(glm::vec2(40,get_speed().y));
		}else if (ae.event == KEY_WALK_LEFT) {
			if (get_current_state() != "walk left") {
				set_current_state("walk left");
			}
			set_speed(glm::vec2(-20,get_speed().y));
		}else if (ae.event == KEY_RUN_LEFT) {
			if (get_current_state() != "walk left") {
				set_current_state("walk left");
			}
			set_speed(glm::vec2(-40,get_speed().y));
		}else {
			if (ae.event == KEY_JUMP) {
				set_speed(glm::vec2(get_speed().x, 50));
			}else if (ae.event == KEY_RUN_JUMP) {
				set_speed(glm::vec2(get_speed().x, 100));
			}else if (ae.event == KEY_STOP) {
				/* decrease speed in x axis direction*/
				set_acceleration(0);
				set_speed(glm::vec2(0, 0));
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
			set_acceleration(0);
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
