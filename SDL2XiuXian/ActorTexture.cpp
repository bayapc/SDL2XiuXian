#include "ActorTexture.h"
ActorTexture::ActorTexture(const char* file_path)
{
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* actorSurface = IMG_Load(file_path);
	//fileName = "res/images/actor.bmp";
	//SDL_Surface* actorSurface = SDL_LoadBMP(fileName.c_str());
	SDL_SetColorKey(actorSurface, SDL_TRUE, SDL_MapRGB(actorSurface->format, 255, 0, 255));
	//actor_texture = SDL_CreateTextureFromSurface(GameWorld::Get_Renderer(), actorSurface);
	actor_texture = SDL_CreateTextureFromSurface(g_renderer, actorSurface);
	SDL_FreeSurface(actorSurface);
}

