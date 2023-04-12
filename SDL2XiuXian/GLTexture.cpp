#include "GLTexture.h"

GLTexture::GLTexture(const char* file_path)
{
	IMG_Init(IMG_INIT_PNG);

	SDL_Surface* bkSurf = IMG_Load(file_path);
	glGenTextures(1, &gl_texture);
	glBindTexture(GL_TEXTURE_2D, gl_texture);
// 	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D	(GL_TEXTURE_2D, 	// target
			 0, 			// level, 0 = base, no minimap,
			GL_RGB, 		// internalformat
			bkSurf->w, 		// width
			bkSurf->h, 		// height
			0, 			// This value must be 0.
			GL_RGB,			// format
			GL_UNSIGNED_BYTE, 	// data type of the pixel datatype
			bkSurf->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(bkSurf);
}
