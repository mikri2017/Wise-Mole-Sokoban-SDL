#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "AppState.h"
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
	CollisionCaps loc_area; // Допустимая зона пространства
	VideoModeMgr vm_mgr;
	SoundMgr* snd_mgr{ nullptr };

	MainHero hero;
	std::vector<WallBlock> w_blocks{};
	std::vector<BoxPlace> b_places{};
	std::vector<Box> boxes{};

	bool fullscren {true};

	const float step = 10; // Длина шага персонажа
public:
	SDLGame() {};

	~SDLGame();

	void init(AppState* as);

	SDL_AppResult proc_event(AppState *as, SDL_Event* event);

	SDL_AppResult app_iter(AppState* as);

	bool check_collisions_immv(GameObject game_o);

	bool check_collisions_boxes(GameObject game_o, float diff_x, float diff_y);

	bool check_for_win();
};
