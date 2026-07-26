#pragma once

#include <SDL3/SDL.h>
#include "VideoModeMgr.h"
#include "game_objects/MainHero.h"
#include "game_objects/CollisionCaps.h"

class SDLGame
{
private:
	SDL_Window* window {nullptr};
	CollisionCaps loc_area; // Допустимая зона пространства
	SDL_Renderer* renderer {nullptr};
	VideoModeMgr vm_mgr;
	int active_vm {0};

	MainHero hero;

	bool fullscren {true};

	const float step = 10; // Длина шага персонажа
public:
	SDLGame(SDL_Window* w, SDL_Renderer* r);

	~SDLGame();

	SDL_AppResult proc_event(void* appstate, SDL_Event* event);

	SDL_AppResult app_iter(void* appstate);
};
