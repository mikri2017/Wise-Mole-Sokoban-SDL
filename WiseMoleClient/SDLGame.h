#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "VideoModeMgr.h"
#include "SoundMgr.h"
#include "game_objects/CollisionCaps.h"
#include "game_objects/MainHero.h"
#include "game_objects/WallBlock.h"
#include "game_objects/BoxPlace.h"
#include "game_objects/Box.h"

class SDLGame
{
private:
	SDL_Window* window {nullptr};
	CollisionCaps loc_area; // Допустимая зона пространства
	SDL_Renderer* renderer {nullptr};
	VideoModeMgr vm_mgr;
	SoundMgr* snd_mgr;

	MainHero hero;
	std::vector<WallBlock> w_blocks{};
	std::vector<BoxPlace> b_places{};
	std::vector<Box> boxes{};

	bool fullscren {true};

	const float step = 10; // Длина шага персонажа
public:
	SDLGame(SDL_Window* w, SDL_Renderer* r);

	~SDLGame();

	SDL_AppResult proc_event(void* appstate, SDL_Event* event);

	SDL_AppResult app_iter(void* appstate);

	bool check_collisions_immv(GameObject game_o);

	bool check_collisions_boxes(GameObject game_o, float diff_x, float diff_y);

	bool check_for_win();
};
