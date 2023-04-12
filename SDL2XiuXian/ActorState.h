#pragma once
#include "Global.h"
//#include "Shader.h"
//#include "Camera.h"
#include "ActorTexture.h"
//#include "ActorCollisionBox.h"

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
//	ActorCollisionBox* get_collision_box(unsigned int idx) {
//		if(idx <3)
//			return box[idx];
//		return NULL;
//	}
	
	~ActorState()
	{
#if true
		free(picture[0]);
		free(picture[1]);
		free(picture[2]);
		free(picture[3]);
		free(picture[4]);
		free(picture[5]);
#endif
		//free(box[0]);
		//free(box[1]);
		//free(box[2]);
	};
private:
	std::string actor_name;
	ActorTexture* picture[6];
	int frame_time;
	int max_index;
	int index;
	//ActorCollisionBox* box[3];
};

