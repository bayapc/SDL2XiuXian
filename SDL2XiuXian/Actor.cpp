#include "Actor.h"
void Actor::update(void)
{
	trails.push_back(Trail(position, current_state));
	if (trails.size() > 50) {
		trails.pop_front();
	}
	if (current_state != NULL) { current_state->update(); }
}

void Actor::scroll_back(void)
{
	Trail tmp = trails.back();
	position = tmp.position;
	current_state = tmp.state_ptr;
	trails.pop_back();
}

