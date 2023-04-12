#pragma once
#include "Global.h"
class ActorTexture
{
public:
	ActorTexture(const char* file_path);
	SDL_Texture* get_texture() const{ return actor_texture; }
	~ActorTexture() {}
private:
	SDL_Texture* actor_texture;

};

