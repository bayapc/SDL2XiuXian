#pragma once
#ifndef __GLOBAL_H__
#define __GLOABAL_H__
#include <windows.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <thread>
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
	KEY_WALK_LEFT,
	KEY_WALK_RIGHT,
	KEY_JUMP,
	KEY_RUN
}KeyEvent;

//using namespace std;

extern SDL_Window* window;
extern SDL_Renderer* g_renderer;
extern SDL_GLContext glContext;

#endif // !__GLOBAL_H__


