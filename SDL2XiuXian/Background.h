#pragma once
#include "Global.h"
#include "GLTexture.h"
#include "Camera.h"
#include "Shader.h"
#include "Actor.h"
#include "EventManager.h"

class Background:public Actor
{
public:
	Background();
	~Background() {}
	void update();
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

