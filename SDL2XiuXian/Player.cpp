#include "Player.h"
void Player::set_current_state(std::string name)
{
	//current_state = std::find(states.begin(),stats.end(),name);
	for (auto it = states.begin(); it != states.end(); it++)
	{
		if ((*it)->get_name() == name) {
			current_state = (*it);
			SDL_QueryTexture(current_state->get_current_picture()->get_texture(),NULL,NULL,&width,&height);
			width = width;
			height = height;
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
	std::string status_str = get_current_state();

	if (p.x < (0+GameWorld::map_offset_x)) {
		p.x = (0+GameWorld::map_offset_x);
		set_position(p);
	}else if (p.x > (GameWorld::screen_width -100 + GameWorld::map_offset_x)) {
		p.x = (GameWorld::screen_width -100 + GameWorld::map_offset_x);
		set_position(p);
	}

	if (p.y < 60) {//low limit Stop
		p.y = 60;
		set_acceleration(0);
		if (get_fly_status()) {
			set_fly_status(0);
			set_speed(glm::vec2(0, 0));
		}else {
			set_speed(glm::vec2(get_speed().x, 0));
		}
		set_position(p);
	}else if (p.y < 200) {
		if (status_str == "fly left") {
			set_current_state("jump left");
		}
		if (status_str == "fly right") {
			set_current_state("jump right");
		}
	}

	if (get_acceleration()) {
		/* send move background event*/
		EventManager* em = EventManager::get_instance();
		ActorEvent e;
		e.uid = em->get_uid_by_name("background");//background
		e.event = KEY_BACKGROUND_MOVE;
		e.speed = get_speed();
		e.speed.x = e.speed.x / 5;
		em->dispatch_event(e);
		//std::cout << "Player:Send Event to background" << std::endl;
	}

	ActorEvent ae = EventManager::get_instance()->get_event(this);
	if (ae.uid != 0) {
		/* const speed in x axis direction*/
		set_acceleration(1);
		int fly = get_fly_status();

		if (ae.event == KEY_DESTROY) {
			std::cout << "Player:Collision Event" << std::endl;
		}

		if (ae.event == KEY_WALK_RIGHT) {
			if ((!fly)&&(status_str != "walk right")) {
				set_current_state("walk right");
			}
			set_speed(glm::vec2(20,get_speed().y));
		}else if (ae.event == KEY_RUN_RIGHT) {
			if ((!fly)&&(status_str != "walk right")) {
				set_current_state("walk right");
			}
			set_speed(glm::vec2(40,get_speed().y));
		}else if (ae.event == KEY_WALK_LEFT) {
			if ((!fly)&&(status_str != "walk left")) {
				set_current_state("walk left");
			}
			set_speed(glm::vec2(-20,get_speed().y));
		}else if (ae.event == KEY_RUN_LEFT) {
			if ((!fly)&&(status_str != "walk left")) {
				set_current_state("walk left");
			}
			set_speed(glm::vec2(-40,get_speed().y));
		}else {
			if (ae.event == KEY_JUMP) {
				set_speed(glm::vec2(get_speed().x, 50));
				if (!fly) {
					set_fly_status(1);
					if ((status_str == "idle left") || (status_str == "walk left")) {
						set_current_state("jump left");
					}else if((status_str == "idle right") || (status_str == "walk right")) {
						set_current_state("jump right");
					}else {
					
					}
				}else {
					if (status_str == "jump left") {
						set_current_state("fly left");
					}
					if (status_str == "jump right") {
						set_current_state("fly right");
					}

					if (status_str == "fly left") {
						set_speed(glm::vec2(-30, get_speed().y));
					}
					if (status_str == "fly right") {
						set_speed(glm::vec2(30, get_speed().y));
					}
				}
			}else if (ae.event == KEY_RUN_JUMP) {
				set_speed(glm::vec2(get_speed().x, 100));
				if (!fly) {
					if ((status_str == "idle left") || (status_str == "walk left")) {
						set_current_state("jump left");
					}else if((status_str == "idle right") || (status_str == "walk right")) {
						set_current_state("jump right");
					}else {
						set_fly_status(1);
						if (status_str == "jump left") {
							set_current_state("fly left");
						}
						if (status_str == "jump right") {
							set_current_state("fly right");
						}
					}
				}else {
					if (status_str == "fly left") {
						set_speed(glm::vec2(-30, get_speed().y));
					}
					if (status_str == "fly right") {
						set_speed(glm::vec2(30, get_speed().y));
					}
				}
			}else if (ae.event == KEY_STOP) {
				if (!fly) {
					/* decrease speed in x axis direction*/
					set_acceleration(0);
					set_speed(glm::vec2(0, 0));
					/* jump state need to be update*/
					if ((status_str == "jump left") || (status_str == "walk left")) {
						set_current_state("idle left");
					}else {
						set_current_state("idle right");
					}
				}
			}
		}
	}else {
		glm::vec2 speed = get_speed();
		if ((speed.x == 0)&&(speed.y == 0)) {
			set_acceleration(0);
			if ((status_str == "idle right") || (status_str == "walk right")||(status_str == "jump right")) {
				set_current_state("idle right");
			}
			else {
				set_current_state("idle left");
			}
		}
	}

	Actor::update();
}
