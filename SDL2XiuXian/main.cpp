#include "Global.h"
#include "Shader.h"
#include "Camera.h"
#include "GameWorld.h"
#include "ActorTexture.h"
#include "Actor.h"
#include "Player.h"
#include "background.h"
#include "Lawn.h"
#include "PhysicsEngine.h"
#include "EventManager.h"
#include "Bullet.h"

#define LAWN_NUM	  60  //lawn_100x100 --> background_3000x720
#define BULLET_NUM    100
// screen
int GAME_WIDTH = 1280;
int GAME_HEIGHT = 720;
// background
int BACKGROUND_WIDTH = 1280;
int BACKGROUND_HEIGHT = 720;

int g_offset_x = 0;
bool g_debug_collision = true;
bool g_debug_reset = false;

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

ActorEvent actor_event = {0, KEY_IDLE,{0,0}};
/********************Actors***************************/
EventManager* event_manager;
Background* bk;
Lawn* lawn[LAWN_NUM];
Player* player1;
Bullet* bullet[BULLET_NUM];
/***********************************************/

void ProcessInput(SDL_Event* keyEvent);

int sys_init(void)
{
	std::cout << "SDL2 XiuXian init!" << std::endl;
	if (SDL_Init(SDL_VIDEO_OPENGL | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) {
		std::cout << "Failed to initialize SDL2!" << std::endl;
		return -1;
	}

	window = SDL_CreateWindow("XiuXian", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, 0);

	if (window == NULL) {
		quitGame = true;
		std::cout << "Failed to initialize window!" << std::endl;
		return -1;
	}

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

	g_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	glContext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, glContext);

	GameWorld* gGame = GameWorld::Get_Instance();
	gGame->Set_Renderer(g_renderer);
	gGame->screen_width = GAME_WIDTH;
	gGame->screen_height = GAME_HEIGHT;

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

	glViewport(0, 0, GAME_WIDTH, GAME_HEIGHT);

	// ----- ICO
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* loadedSurface = IMG_Load("res/images/xiuxian.png");
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));
	SDL_SetWindowIcon(window, loadedSurface);
	SDL_FreeSurface(loadedSurface);

	return 0;
}

void Update(void)
{
	/* background */
	bk->update();
	/* lawn->update() */

	/* bullet */
	for (int i = 0; i < BULLET_NUM; i++) {
		bullet[i]->update();
	}
	/* player */
	player1->update();
}

void Draw(void)
{
	SDL_GL_MakeCurrent(window, glContext);

	SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);

	bk->render();

	/* lawn->render() */
	for (int i = 0; i < LAWN_NUM; i++) {
		glm::vec2 pos = lawn[i]->get_position();
		targetRect1.x = pos.x - GameWorld::map_offset_x; //Transform to screen offset
		if ((targetRect1.x > -100) && (targetRect1.x < GAME_WIDTH)) {
			targetRect1.y = GAME_HEIGHT - pos.y - lawn[i]->height; //invert Y axis
			targetRect1.w = lawn[i]->width;
			targetRect1.h = lawn[i]->height;
			SDL_RenderCopy(g_renderer, lawn[i]->current_state->get_current_picture()->get_texture(), NULL, &targetRect1);

			if (g_debug_collision) {
				targetRect2 = targetRect1;
				targetRect2.w = lawn[i]->get_aabb().bb.x - lawn[i]->get_aabb().aa.x;
				targetRect2.h = lawn[i]->get_aabb().bb.y - lawn[i]->get_aabb().aa.y;
				SDL_RenderDrawRect(g_renderer, &targetRect2);
			}
		}
	}

	/* bullet->render() */
	for (int i = 0; i < BULLET_NUM; i++) {
		if (g_debug_reset) {
			glm::vec2 pos = bullet[i]->get_position();
			pos.y = 10+(i*35)%720;
			bullet[i]->set_position(pos);
			bullet[i]->set_speed(glm::vec2(100,0));
			bullet[i]->set_lifetime(100);
			bullet[i]->set_current_state("start");
		}
		glm::vec2 pos = bullet[i]->get_position();
		targetRect3.x = pos.x - GameWorld::map_offset_x; //Transform to screen offset
		if ((targetRect3.x > 0) && (targetRect3.x < GAME_WIDTH)) {
			/* show on the screen */
			targetRect3.y = GAME_HEIGHT - pos.y - bullet[i]->height; //invert Y axis
			targetRect3.w = bullet[i]->width;
			targetRect3.h = bullet[i]->height;
			SDL_RenderCopy(g_renderer, bullet[i]->current_state->get_current_picture()->get_texture(), NULL, &targetRect3);

			if (g_debug_collision) {
				targetRect2 = targetRect3;
				targetRect2.w = bullet[i]->get_aabb().bb.x - bullet[i]->get_aabb().aa.x;
				targetRect2.h = bullet[i]->get_aabb().bb.y - bullet[i]->get_aabb().aa.y;
				SDL_RenderDrawRect(g_renderer, &targetRect2);
			}
		}
	}

	/* player1->render() */
	glm::vec2 pos = player1->get_position();
	targetRect7.x = pos.x - GameWorld::map_offset_x; //Transform to screen offset
	targetRect7.y = GAME_HEIGHT - pos.y - player1->height; //invert Y axis
	targetRect7.w = player1->width;
	targetRect7.h = player1->height;
	SDL_RenderCopy(g_renderer, player1->current_state->get_current_picture()->get_texture(), NULL, &targetRect7);

	if (g_debug_collision) {
		targetRect2 = targetRect7;
		targetRect2.w = player1->get_aabb().bb.x - player1->get_aabb().aa.x;
		targetRect2.h = player1->get_aabb().bb.y - player1->get_aabb().aa.y;
		SDL_RenderDrawRect(g_renderer, &targetRect2);
	}
	g_debug_reset = false;

	SDL_GL_SwapWindow(window);
}

int main(int argc, char* argv[])
{
	if (sys_init()) {
		std::cout<<"SDL init error"<<std::endl;
		return -1;
	}

	SDL_Event* mainEvent = new SDL_Event();

	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//Note the actor uid
	bk = new Background();//uid = 1
	player1 = new Player(); //uid = 2
	player1->states.push_back(new ActorState("walk right","res/images/xiami/walk_right_0.png",
																 "res/images/xiami/walk_right_1.png",
																 "res/images/xiami/walk_right_2.png",
																 "res/images/xiami/walk_right_3.png",
																COLLISION_LEVEL_NULL));
	player1->states.push_back(new ActorState("idle right","res/images/xiami/walk_right_0.png",
																COLLISION_LEVEL_NULL));
	player1->states.push_back(new ActorState("jump right","res/images/xiami/jump_right_0.png",
																COLLISION_LEVEL_NULL));
	player1->states.push_back(new ActorState("fly right","res/images/xiami/fly_right_0.png",
																COLLISION_LEVEL_NULL));
	player1->states.push_back(new ActorState("walk left","res/images/xiami/walk_left_0.png",
																 "res/images/xiami/walk_left_1.png",
																 "res/images/xiami/walk_left_2.png",
																 "res/images/xiami/walk_left_3.png",
																COLLISION_LEVEL_NULL));
	player1->states.push_back(new ActorState("idle left","res/images/xiami/walk_left_0.png",
																COLLISION_LEVEL_NULL));
	player1->states.push_back(new ActorState("jump left","res/images/xiami/jump_left_0.png",
																COLLISION_LEVEL_NULL));
	player1->states.push_back(new ActorState("fly left","res/images/xiami/fly_left_0.png",
																COLLISION_LEVEL_NULL));
	player1->set_current_state("idle right");

	for (int i= 0; i < LAWN_NUM; i++) {
		lawn[i] = new Lawn();
		lawn[i]->set_position(glm::vec2(i*100,0));
		/* Init Actors resource */
		lawn[i]->states.push_back(new ActorState("spring", "res/images/lawn_100x100.png",
																COLLISION_LEVEL_NULL));
		lawn[i]->set_current_state("spring");

	}

	for (int i = 0; i < BULLET_NUM; i++) {
		bullet[i] = new Bullet();
		bullet[i]->set_position(glm::vec2(rand()%GameWorld::screen_width,10+(i*35)%720));

		bullet[i]->states.push_back(new ActorState("start", "res/images/Bullet/bullet_0.png",
																COLLISION_LEVEL_NULL));
		bullet[i]->states.push_back(new ActorState("normal", "res/images/Bullet/bullet_1.png",
																COLLISION_LEVEL_NULL));
		bullet[i]->states.push_back(new ActorState("explosion", "res/images/Bullet/bullet_2.png",
																COLLISION_LEVEL_NULL));
		bullet[i]->states.push_back(new ActorState("final", "res/images/Bullet/bullet_3.png",
																COLLISION_LEVEL_NULL));
		bullet[i]->set_current_state("start");
	}

	event_manager = EventManager::get_instance();
	event_manager->register_event_type(bk, "background");
	for (int i = 0; i < LAWN_NUM; i++) {
		event_manager->register_event_type(lawn[i], "lawn_"+i);
	}
	event_manager->register_event_type(player1, "player1");
	for (int i = 0; i < BULLET_NUM; i++) {
		event_manager->register_event_type(bullet[i], "bullet_"+i);
	}

	int done = 0;
	int useShader = 0;
	unsigned long lFPSTime = SDL_GetTicks();
	unsigned long frameTime = 0;

	srcRect1.x = 0; srcRect1.y = 0; srcRect1.w = 853; srcRect1.h = 480;

	targetRect1.x = 0; targetRect1.y = 0; targetRect1.w = 100; targetRect1.h = 100;
	targetRect2.x = 500; targetRect2.y = 420; targetRect2.w = 160; targetRect2.h = 240;
	targetRect3.x = 750; targetRect3.y = 420; targetRect3.w = 50; targetRect3.h = 50;
	targetRect4.x = 800; targetRect4.y = 420; targetRect4.w = 160; targetRect4.h = 240;
	targetRect5.x = 960; targetRect5.y = 420; targetRect5.w = 160; targetRect5.h = 240;
	targetRect6.x = 1000; targetRect6.y = 500; targetRect6.w = 112; targetRect6.h = 168;
	targetRect7.x = 50; targetRect7.y = 500; targetRect7.w = 112; targetRect7.h = 168;
	targetRect8.x = 100; targetRect8.y = 420; targetRect8.w = 460; targetRect8.h = 240;

	PhysicsEngine physicsEngine;
	physicsEngine.list.push_back(player1);
	for (int i = 0; i < BULLET_NUM; i++) {
		physicsEngine.list.push_back(bullet[i]);
	}

	GameWorld* gGame = GameWorld::Get_Instance();
	gGame->visible_list.push_back(player1);

	for (int i = 0; i < BULLET_NUM; i++) {
		gGame->visible_list.push_back(bullet[i]);
	}

	while (!quitGame) {
		frameTime = SDL_GetTicks();

		ProcessInput(mainEvent);
//		MouseInput();
		Update();
		Draw();

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
	SDL_GL_DeleteContext(glContext);
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

	ActorEvent e;
	e.uid = 2;//player1
	if (keyEvent->type == SDL_KEYUP) {
		if (keyEvent->key.keysym.sym == SDLK_ESCAPE) {
			quitGame = true;
		}
		e.event = KEY_STOP;
		event_manager->dispatch_event(e);
	}else if (keyEvent->type == SDL_KEYDOWN) {
		//std::cout << "key:"<< keyEvent->key.keysym.sym <<"mod"<< keyEvent->key.keysym.mod <<std::endl;
		if (keyEvent->key.keysym.mod == KMOD_NUM) {
			if (keyEvent->key.keysym.sym == SDLK_d) {
				e.event = KEY_WALK_RIGHT;
				event_manager->dispatch_event(e);
			}
			if (keyEvent->key.keysym.sym == SDLK_a) {
				e.event = KEY_WALK_LEFT;
				event_manager->dispatch_event(e);
			}
			if (keyEvent->key.keysym.sym == SDLK_w) {
				e.event = KEY_JUMP;
				event_manager->dispatch_event(e);
			}
			if (keyEvent->key.keysym.sym == SDLK_s) {
			}
			if (keyEvent->key.keysym.sym == SDLK_t) {
				g_debug_collision = !g_debug_collision;
			}
			if (keyEvent->key.keysym.sym == SDLK_r) {
				g_debug_reset = true;
			}
		}else if(keyEvent->key.keysym.mod == (KMOD_NUM | KMOD_LSHIFT)){
			if (keyEvent->key.keysym.sym == SDLK_d) {
				e.event = KEY_RUN_RIGHT;
				event_manager->dispatch_event(e);
			}
			if (keyEvent->key.keysym.sym == SDLK_a) {
				e.event = KEY_RUN_LEFT;
				event_manager->dispatch_event(e);
			}
			if (keyEvent->key.keysym.sym == SDLK_w) {
				e.event = KEY_RUN_JUMP;
				event_manager->dispatch_event(e);
			}
			if (keyEvent->key.keysym.sym == SDLK_s) {
			}
		}
	}
}

