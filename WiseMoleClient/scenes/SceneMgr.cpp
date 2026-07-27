#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	// Заполним запас сцен
	Scene* scn = new SCN_Level();
	scn->set_name("game_level");

	scenes.push_back(scn);

	// Устанавливаем активную, по умолчанию
	scene_id = 0;
}

SceneMgr::~SceneMgr()
{
	for (auto& scn : scenes)
	{
		if (scn)
			delete scn;
	}
}

SDL_AppResult SceneMgr::app_iter(AppState* as)
{
	// Очередной цикл отработки программы
	if (scenes.size() > scene_id)
		return scenes[scene_id]->app_iter(as);
	else
	{
		SDL_Log("Error! Active scene_id [%i] more than scenes count!", scene_id);
		return SDL_APP_FAILURE;
	}
}

SDL_AppResult SceneMgr::proc_mouse_motion(AppState* as, float x, float y)
{
	if (scenes.size() > scene_id)
	{
		GameReaction gr = scenes[scene_id]->proc_mouse_motion(as, x, y);
		return proc_game_reaction(gr);
	}
	else
	{
		SDL_Log("Error! Active scene_id [%i] more than scenes count!", scene_id);
		return SDL_APP_FAILURE;
	}
}

SDL_AppResult SceneMgr::proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event)
{
	if (scenes.size() > scene_id)
	{
		GameReaction gr = scenes[scene_id]->proc_mouse_button_event(as, m_btn_event);
		return proc_game_reaction(gr);
	}
	else
	{
		SDL_Log("Error! Active scene_id [%i] more than scenes count!", scene_id);
		return SDL_APP_FAILURE;
	}
}

SDL_AppResult SceneMgr::proc_keyboard_keydown(AppState* as, SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_ESCAPE)
	{
		return SDL_APP_SUCCESS;
	}

	if (scenes.size() > scene_id)
	{
		GameReaction gr = scenes[scene_id]->proc_keyboard_keydown(as, scancode);
		return proc_game_reaction(gr);
	}
	else
	{
		SDL_Log("Error! Active scene_id [%i] more than scenes count!", scene_id);
		return SDL_APP_FAILURE;
	}
}

SDL_AppResult SceneMgr::proc_game_reaction(GameReaction gr)
{
	if (gr.gr_type == GRType::GR_CHG_SCENE)
	{
		std::cout << "Next Scene: " << gr.adv_inf << std::endl;
	}

	return SDL_APP_CONTINUE;
}
