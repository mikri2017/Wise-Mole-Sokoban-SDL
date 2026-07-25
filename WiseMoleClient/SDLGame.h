#pragma once

#include <SDL3/SDL.h>
#include "VideoModeMgr.h"

class SDLGame
{
private:
	SDL_Window* window {nullptr};
	int win_w, win_h; // Размеры окна
	SDL_Renderer* renderer {nullptr};
	VideoModeMgr vm_mgr;
	int active_vm {0};

	SDL_FRect fr {0, 0, 50, 50};
	bool fullscren {true};

	const int step = 10; // Длина шага персонажа
public:
	SDLGame(SDL_Window* w, SDL_Renderer* r);

	~SDLGame();

	SDL_AppResult proc_event(void* appstate, SDL_Event* event);

	SDL_AppResult app_iter(void* appstate);
};
