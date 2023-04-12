#include "ActorState.h"

ActorState::ActorState(std::string name,const char* pic1,CollisionLevel collision_level)
{
	actor_name = name;
	index = 0;
	frame_time = 0;
	max_index = 1;
	picture[0] = new ActorTexture(pic1);
	if (collision_level == COLLISION_LEVEL_NULL) {
	}

}

ActorState::ActorState(std::string name,const char* pic1,const char* pic2,const char* pic3,const char* pic4,CollisionLevel collision_level)
{
	actor_name = name;
	std::cout <<"ActorState:"<< actor_name << std::endl;
	index = 0;
	frame_time = 0;
	max_index = 4;
	picture[0] = new ActorTexture(pic1);
	picture[1] = new ActorTexture(pic2);
	picture[2] = new ActorTexture(pic3);
	picture[3] = new ActorTexture(pic4);

	if (collision_level == COLLISION_LEVEL_NULL) {
	}
}

void ActorState::update()
{
	if (frame_time++ > 10) {
		frame_time = 0;
		index++;
		if (index >= max_index) {
			index = 0;
		}
	}
}
