#include "background.h"
#include "Shader.h"

Background::Background():
	width(1280),
	height(720),
	position(0.0f, 0.0f, 0.0f)
{
#if true
	// positions
	glm::vec3 pos1(-2.0f, 1.0f, 0.0f);
	glm::vec3 pos2(-2.0f, -1.0f, 0.0f);
	glm::vec3 pos3(6.0f, -1.0f, 0.0f);
	glm::vec3 pos4(6.0f, 1.0f, 0.0f);
#if true
	// texture Coords (swapped y coordinates because texture is flipped upside down)
	// texture coordinates
	glm::vec2 uv1(0.0f, 0.0f);
	glm::vec2 uv2(0.0f, 1.0f);
	glm::vec2 uv3(1.0f, 1.0f);
	glm::vec2 uv4(1.0f, 0.0f);
#else
	// texture coordinates
	glm::vec2 uv1(0.0f, 1.0f);
	glm::vec2 uv2(0.0f, 0.0f);
	glm::vec2 uv3(1.0f, 0.0f);
	glm::vec2 uv4(1.0f, 1.0f);
#endif
	// normal vector
	glm::vec3 nm(0.0f, 0.0f, 1.0f);

	// calculate tangent/bitangent vectors of both triangles
	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;
	// triangle 1
	// ----------
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

	// triangle 2
	// ----------
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);


	float quadVertices[] = {
		// positions            // normal         // texcoords  // tangent                          // bitangent
		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
	};
	// configure plane VAO
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
#else
	planeV = new float[30]{
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
	  -2.0f, -1.0f,   0.0f,  0.0f,  1.0f,
	   6.0f, -1.0f,   0.0f,  1.0f,  1.0f,
	   6.0f,  1.0f,  0.0f,  1.0f,  0.0f,

	  -2.0f, -1.0f,    0.0f,  0.0f,  1.0f,
	   6.0f, 1.0f,  0.0f,  1.0f,  0.0f,
	  -2.0f, 1.0f,  0.0f,  0.0f,  0.0f
	};
	// plane VAO
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), planeV, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(planeV), &planeV, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
#endif
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	free(planeV);

	// transparent vegetation locations
	  // --------------------------------
	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

	glEnable(GL_TEXTURE_2D);


	// camera
	bkCamera = new Camera(glm::vec3(0.0f, 0.0f, 2.4f));

	// lighting info
	// -------------
	lightPos = glm::vec3(0.5f, 1.0f, 1.3f);

	// build and compile our shader zprogram
	// ------------------------------------
#if true
	bkShader = new Shader("res/shader/normal_mapping.vs", "res/shader/normal_mapping.fs");
	std::cout << "OpenGL shader ok!" << std::endl;

	bkTextures.push_back(new GLTexture("res/images/background.png"));
	bkTextures.push_back(new GLTexture("res/images/background_normal.png"));
	bkTextures.push_back(new GLTexture("res/images/actor.png"));

	bkShader->use();
	bkShader->setInt("diffuseMap", 0);
	bkShader->setInt("normalMap", 1);
#else
	bkShader = new Shader("res/shader/bkBase.vs", "res/shader/bkBase.fs");
	std::cout << "OpenGL shader ok!" << std::endl;

	bkTextures.push_back(new GLTexture("res/images/background.png"));
	bkTextures.push_back(new GLTexture("res/images/actor.png"));

	bkShader->use();
	bkShader->setInt("texture1", 0);
#endif
	// pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
	   // -----------------------------------------------------------------------------------------------------------
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	bkShader->setMat4("projection", projection);
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(position));
	bkShader->setMat4("model", model);
}

void Background::render(void)
{
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearColor(0.01f, 0.1f, 1.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// draw objects
	bkShader->use();
	bkShader->setMat4("view", bkCamera->GetViewMatrix());
#if true
     bkShader->setVec3("viewPos", bkCamera->Position);
	 bkShader->setVec3("lightPos", lightPos);
	 glActiveTexture(GL_TEXTURE0);
	 glBindTexture(GL_TEXTURE_2D, bkTextures[0]->get_texture());
	 glActiveTexture(GL_TEXTURE1);
	 glBindTexture(GL_TEXTURE_2D, bkTextures[1]->get_texture());
#else
	glBindTexture(GL_TEXTURE_2D, (*(bkTextures.begin()))->get_texture());
#endif
	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Background::update(glm::vec2 pos)
{
	position.x += pos.x;
	if (position.x < 0) {
		position.x = 0;
	}else if (position.x > (bkTextures[0]->get_width())) {
		position.x = bkTextures[0]->get_width();
	}else {
		bkCamera->Position.x = position.x * 0.001;
	}
	//std::cout << "bkPostion:" << position.x <<" bkTexture width:" <<bkTextures[0]->get_width()<< std::endl;
	for (unsigned int i = 0; i < vegetation.size(); i++)
	{
		vegetation[i].x += pos.x * 0.01;
	}

}
