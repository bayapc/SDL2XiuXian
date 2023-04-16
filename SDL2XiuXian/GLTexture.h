#pragma once
#include "Global.h"

class GLTexture
{
public:
	GLTexture(const char* file_path);
	GLuint get_texture()	const	{ return gl_texture; }
	int get_width()			const	{ return width; }
	int get_height()		const	{ return height; }
	~GLTexture() {}
private:
	GLuint gl_texture;
	int width;
	int height;
};

