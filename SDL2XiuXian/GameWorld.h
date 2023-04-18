#pragma once
#include "Global.h"
class GameWorld
{
public:
	static GameWorld* Get_Instance();
	static SDL_Renderer* Get_Renderer() { return gRenderer; }
	static void Set_Renderer(SDL_Renderer* r) { gRenderer = r; }
private:
	GameWorld(){}
	~GameWorld() {}
	static SDL_Renderer* gRenderer;
	static GameWorld* instance;
};

