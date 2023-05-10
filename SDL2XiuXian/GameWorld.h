#pragma once
#include "Global.h"
#include "Actor.h"

class GameWorld
{
public:
	static GameWorld* Get_Instance();
	static SDL_Renderer* Get_Renderer() { return gRenderer; }
	static void Set_Renderer(SDL_Renderer* r) { gRenderer = r; }
	static int screen_width;
	static int screen_height;
	static std::vector<Actor*> visible_list;
	static std::vector<Actor*> total_list;
private:
	GameWorld(){}
	~GameWorld() {}
	static SDL_Renderer* gRenderer;
	static GameWorld* instance;
};

