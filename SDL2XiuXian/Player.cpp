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

void Player::update(int v)
{
	glm::vec2 p = get_position();
	p.x += v*2;
	if (p.x < 0) {
		p.x = 0;
	}else if (p.x > GameWorld::screen_width -100) {
		p.x = GameWorld::screen_width -100;
	}
	if (p.y <= 220) {//low limit
		p.y = 220;
		set_speed(glm::vec2(0, 0));
	}

	if (v == 1) {
		if (get_current_state() != "walk right") {
			set_current_state("walk right");
		}
	}
	else if (v == -1) {
		if (get_current_state() != "walk left") {
			set_current_state("walk left");
		}
	}else {
		if ((v == 2)) {
			set_speed(glm::vec2(0,50));
			std::cout << "Jump" << std::endl;
		}
		if ((get_current_state() == "idle right") || (get_current_state() == "walk right")) {
			set_current_state("idle right");
		}else {
			set_current_state("idle left");
		}
	}
	set_position(p);

	Actor::update();
}
