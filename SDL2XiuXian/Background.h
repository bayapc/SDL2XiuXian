#pragma once
#include "Global.h"
#include "GLTexture.h"
#include "Camera.h"
#include "Shader.h"

class Background
{
public:
	Background();
	~Background() {}
	void update(glm::vec2 pos);
	void render();
private:
	int width;
	int height;
	glm::vec3 position;
	glm::vec3 lightPos;

	// set up vertex data (and buffer(s)) and configure vertex attributes
	//float* cubeV;
	float* planeV;
	//float* transparentV;
	std::vector<glm::vec3> vegetation;
	// ------------------------------------------------------------------
	unsigned int cubeVAO;
	unsigned int cubeVBO;
	unsigned int planeVAO;
	unsigned int planeVBO;
	unsigned int transparentVAO;
	unsigned int transparentVBO;

	Camera* bkCamera;
	Shader* bkShader;
	std::vector<GLTexture*> bkTextures;
	int weather;
	int season;
};

