#include "background.h"
#include "Shader.h"

Background::Background():
	width(1280),
	height(720),
	position(0.0f, 0.0f, 0.0f)
{
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
	glBufferData(GL_ARRAY_BUFFER, 30*sizeof(float), planeV, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(planeV), &planeV, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

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

	// build and compile our shader zprogram
	// ------------------------------------
	bkShader = new Shader("res/shader/bkBase.vs", "res/shader/bkBase.fs");
	std::cout << "OpenGL shader ok!" << std::endl;

	bkTextures.push_back(new GLTexture("res/images/background.png"));
	bkTextures.push_back(new GLTexture("res/images/actor.png"));

	bkShader->use();
	bkShader->setInt("texture1", 0);

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
	glBindVertexArray(planeVAO);
	glBindTexture(GL_TEXTURE_2D, (*(bkTextures.begin()))->get_texture());
	bkShader->setMat4("view", bkCamera->GetViewMatrix());
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
	std::cout << "bkPostion:" << position.x <<" bkTexture width:" <<bkTextures[0]->get_width()<< std::endl;
	for (unsigned int i = 0; i < vegetation.size(); i++)
	{
		vegetation[i].x += pos.x * 0.01;
	}

}
