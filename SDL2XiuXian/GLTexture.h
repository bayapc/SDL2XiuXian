#pragma once
#include "Global.h"

class GLTexture
{
public:
	GLTexture(const char* file_path);
	GLuint get_texture() const{ return gl_texture; }
	~GLTexture() {}
private:
	GLuint gl_texture;
};

