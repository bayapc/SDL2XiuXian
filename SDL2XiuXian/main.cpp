#include "Global.h"
#include "Shader.h"
#include "Camera.h"
#include "GameWorld.h"
#include "ActorTexture.h"
#include "Actor.h"
#include "Player.h"
#include "background.h"

// screen
int GAME_WIDTH = 1280;
int GAME_HEIGHT = 720;
// background
int BACKGROUND_WIDTH = 1280;
int BACKGROUND_HEIGHT = 720;

SDL_Window* window;
SDL_Renderer* g_renderer;
SDL_GLContext glContext;
//GameWorld gGameWorld;
bool quitGame = false;
unsigned long MIN_FRAME_TIME = 17;
SDL_Rect srcRect1;
SDL_Rect targetRect1;
SDL_Rect targetRect2;
SDL_Rect targetRect3;
SDL_Rect targetRect4;
SDL_Rect targetRect5;
SDL_Rect targetRect6;
SDL_Rect targetRect7;
SDL_Rect targetRect8;
int actor_status = 0;

void ProcessInput(SDL_Event* keyEvent);

int sys_init(void)
{
	std::cout << "SDL2 Weather System init!" << std::endl;
	if (SDL_Init(SDL_VIDEO_OPENGL | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) {
		std::cout << "Failed to initialize SDL2!" << std::endl;
		return -1;
	}
#if false
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}
#endif
	window = SDL_CreateWindow("XiuXian", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, 0);

	if (window == NULL) {
		quitGame = true;
		std::cout << "Failed to initialize window!" << std::endl;
		return -1;
	}

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

	//SDL_Renderer* g_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	g_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	glContext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, glContext);

	GameWorld* gGame = GameWorld::Get_Instance();
	gGame->Set_Renderer(g_renderer);

	SDL_RendererInfo rendererInfo;
	SDL_GetRendererInfo(g_renderer, &rendererInfo);

	if (!strncmp(rendererInfo.name, "opengl", 6)) {
		std::cout << "Es OpenGL!" << std::endl;
		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
	}

	//Make a target texture to render too
	//SDL_Texture *texTarget = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, GAME_WIDTH, GAME_HEIGHT);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetSwapInterval(1);

	// Create a double-buffered draw context
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetSwapInterval(1);
	glViewport(0, 0, GAME_WIDTH, GAME_HEIGHT);

	// Set Mode to GL_PROJECTION
		//
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	// Set projection MATRIX to ORTHO
	// I use a near plane value of -1, and a far plane value of 1, which is what works best for 2D games.
	//glOrtho(0.0, GAME_WIDTH, 0.0, GAME_HEIGHT, -1.0, 1.0);

	// Setting Mode to GL_MODELVIEW
	//glMatrixMode(GL_MODELVIEW);

	// -----------------------------
	//glEnable(GL_DEPTH_TEST);

	// ----- ICO
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* loadedSurface = IMG_Load("res/images/xiuxian.png");
	//std::string fileName = "res/images/ico.bmp";
	//SDL_Surface* loadedSurface = SDL_LoadBMP(fileName.c_str());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));
	SDL_SetWindowIcon(window, loadedSurface);
	SDL_FreeSurface(loadedSurface);

	return 0;
}

int main(int argc, char* argv[])
{
	if (sys_init()) {
		std::cout<<"SDL init error"<<std::endl;
		return -1;
	}

	SDL_Event* mainEvent = new SDL_Event();

	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

#if true
#if false
#if false
	// ----- actor
	//Put your own bmp image here
	//IMG_Init(IMG_INIT_JPG);
	//SDL_Surface* bkSurf = IMG_Load("res/images/ground.jpg");
	//SDL_Surface* bkSurf = IMG_Load("res/images/background.bmp");
	std::string fileName = "res/images/background.bmp";
	SDL_Surface* bkSurf  = SDL_LoadBMP(fileName.c_str());
	BACKGROUND_WIDTH = bkSurf->w;
	BACKGROUND_HEIGHT = bkSurf->h;
	SDL_Texture* backgroundTex = SDL_CreateTextureFromSurface(g_renderer, bkSurf);
	SDL_FreeSurface(bkSurf);
#endif
	//Shader* bkShader = new Shader("res/shader/blending.vs", "res/shader/blending.fs");
	Shader* bkShader = new Shader("res/shader/texture.vs", "res/shader/texture.fs");
	std::cout << "OpenGL shader ok!" << std::endl;


    float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        -1.0f, -1.0f,   0.0f,  0.0f,  1.0f,
         3.0f, -1.0f,   0.0f,  1.0f,  1.0f,
         3.0f,  1.0f,  0.0f,  1.0f,  0.0f,

        -1.0f, -1.0f,    0.0f,  0.0f,  1.0f,
         3.0f, 1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f, 1.0f,  0.0f,  0.0f,  0.0f
    };

    // transparent VAO
    unsigned int transparentVAO, transparentVBO;
    glGenVertexArrays(1, &transparentVAO);
    glGenBuffers(1, &transparentVBO);
    glBindVertexArray(transparentVAO);
    glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), &transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	GLTexture* bkTexture = new GLTexture("res/images/background.png");

    // transparent vegetation locations
    // --------------------------------
    std::vector<glm::vec3> vegetation 
    {
        glm::vec3(-100.5f, 100.0f, -0.48f),
        glm::vec3( 100.5f, 100.0f, 0.51f),
        glm::vec3( 100.0f, 100.0f, 0.7f),
        glm::vec3(-100.3f, 100.0f, -2.3f),
        glm::vec3 (100.5f, 100.0f, -0.6f)
    };

#else
	Background bk;
#endif
	Player player1;
	player1.states.push_back(new ActorState("walk right","res/images/amy/wright_0.png",
																 "res/images/amy/wright_1.png",
																 "res/images/amy/wright_2.png",
																 "res/images/amy/wright_3.png",
																COLLISION_LEVEL_NULL));
	player1.states.push_back(new ActorState("idle right","res/images/amy/wright_0.png",
																COLLISION_LEVEL_NULL));
	player1.states.push_back(new ActorState("walk left","res/images/amy/wleft_0.png",
																 "res/images/amy/wleft_1.png",
																 "res/images/amy/wleft_2.png",
																 "res/images/amy/wleft_3.png",
																COLLISION_LEVEL_NULL));
	player1.states.push_back(new ActorState("idle left","res/images/amy/wleft_0.png",
																COLLISION_LEVEL_NULL));
	player1.set_current_state("idle right");

	//SDL_RenderCopy(g_renderer, backgroundTex, NULL, NULL);
#endif
	//Make a target texture to render too
	//SDL_Texture* texTarget = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, GAME_WIDTH, GAME_HEIGHT);

	int done = 0;
	int useShader = 0;
	unsigned long lFPSTime = SDL_GetTicks();
	unsigned long frameTime = 0;

	srcRect1.x = 0; srcRect1.y = 0; srcRect1.w = 853; srcRect1.h = 480;

	targetRect1.x = 600; targetRect1.y = 420; targetRect1.w = 160; targetRect1.h = 240;
	targetRect2.x = 500; targetRect2.y = 420; targetRect2.w = 160; targetRect2.h = 240;
	targetRect3.x = 750; targetRect3.y = 420; targetRect3.w = 160; targetRect3.h = 240;
	targetRect4.x = 800; targetRect4.y = 420; targetRect4.w = 160; targetRect4.h = 240;
	targetRect5.x = 960; targetRect5.y = 420; targetRect5.w = 160; targetRect5.h = 240;
	targetRect6.x = 1000; targetRect6.y = 500; targetRect6.w = 112; targetRect6.h = 168;
	targetRect7.x = 50; targetRect7.y = 500; targetRect7.w = 112; targetRect7.h = 168;
	targetRect8.x = 100; targetRect8.y = 420; targetRect8.w = 460; targetRect8.h = 240;
	//targetRect.x = 0; targetRect.y = 0; targetRect.w = 64; targetRect.h = 84;

	while (!quitGame) {
		frameTime = SDL_GetTicks();
		SDL_GL_MakeCurrent(window, glContext);

#if true
		if (((actor_status < 0) && (player1.get_position().x < GAME_WIDTH / 3))||
			((actor_status > 0) && (player1.get_position().x > GAME_WIDTH / 2))){
			bk.update(glm::vec2(actor_status, 0));
		}
		bk.render();
#endif

#if false
		SDL_RenderCopy(g_renderer, backgroundTex, &srcRect1, NULL);
		targetRect1.x += actor_status;
		SDL_RenderCopy(g_renderer, actorTex, NULL, &targetRect1);
		targetRect2.x += actor_status;
		SDL_RenderCopy(g_renderer, actorTex, NULL, &targetRect2);
		targetRect3.x += actor_status;
		SDL_RenderCopy(g_renderer, actorTex, NULL, &targetRect3);
		targetRect4.x += actor_status;
		SDL_RenderCopy(g_renderer, actorTex, NULL, &targetRect4);
		targetRect5.x += actor_status;
		SDL_RenderCopy(g_renderer, actorTex, NULL, &targetRect5);
		targetRect6.x += actor_status;
		SDL_RenderCopy(g_renderer, actorTex, NULL, &targetRect6);
		//SDL_GL_BindTexture(actorTex, NULL, NULL);
		
		if (amyframe_index > 159) {
			amyframe_index = 0;
		}
		SDL_RenderCopy(g_renderer, amyTex[amyframe_index++/40], NULL, &targetRect7);
		SDL_RenderCopy(g_renderer, soldierTex[amyframe_index++/40], NULL, &targetRect8);
#else
#if false
		if (actor_status == 1) {
			if (player1.get_current_state() != "walk right") {
				player1.set_current_state("walk right");
			}
		}else if (actor_status == -1) {
			if (player1.get_current_state() != "walk left") {
				player1.set_current_state("walk left");
			}
		}else {
			if ((player1.get_current_state() == "idle right") || (player1.get_current_state() == "walk right")) {
				player1.set_current_state("idle right");
			}
			else {
				player1.set_current_state("idle left");
			}
		}
#endif
		player1.update(actor_status);
		glm::vec2 pos = player1.get_position();
		std::cout << "player Position:(" << pos.x<<"," << pos.y <<")" << std::endl;
		//SDL_RenderCopy(g_renderer, player1.current_state->get_current_picture()->get_texture(), NULL, &targetRect1);
		//SDL_RenderCopy(g_renderer, player1.current_state->get_current_picture()->get_texture(), NULL, &targetRect2);
		//SDL_RenderCopy(g_renderer, player1.current_state->get_current_picture()->get_texture(), NULL, &targetRect3);
		//SDL_RenderCopy(g_renderer, player1.current_state->get_current_picture()->get_texture(), NULL, &targetRect4);
		//SDL_RenderCopy(g_renderer, player1.current_state->get_current_picture()->get_texture(), NULL, &targetRect5);
		//SDL_RenderCopy(g_renderer, player1.current_state->get_current_picture()->get_texture(), NULL, &targetRect6);
		//targetRect7.x += actor_status;
		targetRect7.x = pos.x;
		targetRect7.y = pos.y;
		//player1.set_position(glm::vec2(targetRect7.x, targetRect7.y));
		SDL_RenderCopy(g_renderer, player1.current_state->get_current_picture()->get_texture(), NULL, &targetRect7);
		//SDL_RenderCopy(g_renderer, player1.current_state->get_current_picture()->get_texture(), NULL, &targetRect8);
#endif

		//SDL_RenderPresent(g_renderer);
		SDL_GL_SwapWindow(window);

		ProcessInput(mainEvent);
//		MouseInput();
//		Update();
//		Draw();

		/*CCFG::getText()->Draw(rR, "FPS:" + std::to_string(iNumOfFPS), CCFG::GAME_WIDTH - CCFG::getText()->getTextWidth("FPS:" + std::to_string(iNumOfFPS), 8) - 8, 5, 8);

		if(SDL_GetTicks() - 1000 >= lFPSTime) {
			lFPSTime = SDL_GetTicks();
			iNumOfFPS = iFPS;
			iFPS = 0;
		}

		++iFPS;*/
		
		if(SDL_GetTicks() - frameTime < MIN_FRAME_TIME) {
			SDL_Delay(MIN_FRAME_TIME - (SDL_GetTicks () - frameTime));
		}
	}

	//SDL_DestroyTexture(texTarget);
	//SDL_DestroyTexture(backgroundTex);
	//SDL_GL_DeleteContext(glContext);
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void ProcessInput(SDL_Event* keyEvent)
{
	SDL_PollEvent(keyEvent);
	if (keyEvent->type == SDL_QUIT) {
			quitGame = true;
	}

	if(keyEvent->type == SDL_WINDOWEVENT) {
		switch(keyEvent->window.event) {
			case SDL_WINDOWEVENT_FOCUS_LOST:
				break;
		}
	}

	if (keyEvent->type == SDL_KEYUP) {
		if (keyEvent->key.keysym.sym == SDLK_ESCAPE) {
			quitGame = true;
		}
		actor_status = 0;
	}
	else if (keyEvent->type == SDL_KEYDOWN) {
		if (keyEvent->key.keysym.sym == SDLK_d) {
			///targetRect.x += 1;
			//targetRect.x = 1;
			actor_status = 1;
		}
		if (keyEvent->key.keysym.sym == SDLK_a) {
			//targetRect.x -= 1;
			//targetRect.x = -1;
			actor_status = -1;
		}
		if (keyEvent->key.keysym.sym == SDLK_w) {
			//targetRect.x += 1;
			//targetRect7.y -= 30;
			targetRect7.y = 300;
			if (actor_status < 0) {
				actor_status -= 1;
			}else {
				actor_status += 1;
			}
		}
		if (keyEvent->key.keysym.sym == SDLK_s) {
			//targetRect.x = 0;
			actor_status = 0;
			targetRect7.y = 500;
		}
	}
}

