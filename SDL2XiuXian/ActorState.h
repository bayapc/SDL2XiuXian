#pragma once
#include "Global.h"
#include "ActorTexture.h"

class ActorState
{
public:
	ActorState(){}
	ActorState(std::string name,const char* pic1,CollisionLevel collision_level);
	//ActorState(std::string name,const char* pic1,const char* pic2,CollisionLevel collision_level,);
	//ActorState(std::string name,const char* pic1,const char* pic2,const char* pic3,CollisionLevel collision_level,);
	ActorState(std::string name,const char* pic1,const char* pic2,const char* pic3,const char* pic4,CollisionLevel collision_level);
	//ActorState(std::string name,const char* pic1,const char* pic2,const char* pic3,const char* pic4,const char* pic5,CollisionLevel collision_level);
	//ActorState(std::string name,const char* pic1,const char* pic2,const char* pic3,const char* pic4,const char* pic5,const char* pic6,CollisionLevel collision_level);
	void update();
	std::string get_name() { return actor_name; }
	ActorTexture* get_current_picture(void) { return picture[index]; }
	
	~ActorState()
	{
		free(picture[0]);
		free(picture[1]);
		free(picture[2]);
		free(picture[3]);
		free(picture[4]);
		free(picture[5]);
	};
private:
	std::string actor_name;
	ActorTexture* picture[6];
	int frame_time;
	int max_index;
	int index;
};

