#pragma once

#include <SDL3/SDL.h>
#include "VideoModeMgr.h"

class SDLGame
{
private:
	SDL_Window* window {nullptr};
	SDL_Renderer* renderer {nullptr};
	VideoModeMgr vm_mgr;
	int active_vm {0};
	std::vector<GameVideoModeStr> vvm_str;

	SDL_FRect fr {0, 0, 50, 50};
	bool fullscren {true};
public:
	SDLGame(SDL_Window* w, SDL_Renderer* r);

	~SDLGame();

	SDL_AppResult proc_event(void* appstate, SDL_Event* event);

	SDL_AppResult app_iter(void* appstate);
};
