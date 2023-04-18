#include "GameWorld.h"
SDL_Renderer* GameWorld::gRenderer = NULL;
GameWorld* GameWorld::instance = NULL;
GameWorld* GameWorld::Get_Instance()
{
	if (instance == NULL) {
		instance = new GameWorld();
	}
	return instance;
}
