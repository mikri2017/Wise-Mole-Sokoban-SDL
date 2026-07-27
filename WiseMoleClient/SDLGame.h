#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "AppState.h"
#include "VideoModeMgr.h"
#include "scenes/SceneMgr.h"

class SDLGame
{
private:
	SceneMgr* scn_mgr{ nullptr };
	VideoModeMgr vm_mgr;

	bool fullscren {true};
public:
	~SDLGame();

	void init(AppState* as);

	SDL_AppResult proc_event(AppState* as, SDL_Event* event);

	SDL_AppResult app_iter(AppState* as);
};
