#include "Lawn.h"

void Lawn::set_current_state(std::string name)
{
	for (auto it = states.begin(); it != states.end(); it++)
	{
		if ((*it)->get_name() == name) {
			current_state = (*it);
		}
	}
}

std::string Lawn::get_current_state(void)
{
	return current_state->get_name();
}


