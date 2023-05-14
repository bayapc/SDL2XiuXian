#include "GameWorld.h"
SDL_Renderer* GameWorld::gRenderer = NULL;
GameWorld* GameWorld::instance = NULL;
int GameWorld::screen_width = 1280;
int GameWorld::screen_height = 720;
int GameWorld::map_offset_x = 0;
std::vector<Actor*> GameWorld::visible_list;
std::vector<Actor*> GameWorld::total_list;

GameWorld* GameWorld::Get_Instance()
{
	if (instance == NULL) {
		instance = new GameWorld();
	}
	return instance;
}
