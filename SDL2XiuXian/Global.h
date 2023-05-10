#pragma once
#ifndef __GLOBAL_H__
#define __GLOABAL_H__
#include <windows.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <thread>
#include <map>
#include <sdl.h>
#include <SDL_image.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


enum CollisionLevel {
	COLLISION_LEVEL_NULL,
	COLLISION_LEVEL_1,
	COLLISION_LEVEL_2,
	COLLISION_LEVEL_3
};

typedef enum {
	KEY_IDLE,
	KEY_STOP,
	KEY_WALK_LEFT,
	KEY_WALK_RIGHT,
	KEY_JUMP,
	KEY_RUN_LEFT,
	KEY_RUN_RIGHT,
	KEY_RUN_JUMP,
	KEY_FLY,
	KEY_ATTACK,
	KEY_BACKGROUND_MOVE,
	KEY_DESTROY,
	KEY_AUDIO_METAL,
}KeyEvent;

typedef enum {
	METALLIC,
	WOOD,
	BRICK
}MATERIAL;

typedef struct {
	Uint32 uid;
	KeyEvent event;
	glm::vec2 speed;
}ActorEvent;

typedef struct {
	glm::vec2 aa;
	glm::vec2 bb;
}AABB_BOX;

/*
 * Global Actor Unique ID.
 * Start from logic one,0 means actor in preview init status.
*/
inline Uint32 alloc_actor_uid(void) {
	static Uint32 actor_uid = 1;
	return actor_uid++;
}
//using namespace std;

extern SDL_Window* window;
extern SDL_Renderer* g_renderer;
extern SDL_GLContext glContext;

#endif // !__GLOBAL_H__


