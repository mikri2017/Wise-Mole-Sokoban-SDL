#pragma once

#include <vector>
#include "Scene.h"
#include "SCN_MainMenu.h"
#include "SCN_Level.h"
#include "../AppState.h"

class SceneMgr
{ // Менеджер сцен будет знать, какие у него есть сцены и как их запускать друг за другом!
private:
	int scene_id{ 0 };
	int scene_id_prev{ 0 }; // ID предыдущей сцены
	std::vector<Scene*> scenes{};
public:
	SceneMgr();

	~SceneMgr();

	SDL_AppResult app_iter(AppState* as);

	SDL_AppResult proc_mouse_motion(AppState* as, float x, float y);

	SDL_AppResult proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event);

	SDL_AppResult proc_keyboard_keydown(AppState* as, SDL_Scancode scancode);

	SDL_AppResult proc_game_reaction(GameReaction gr);

	int find_scene(std::string name);
};
