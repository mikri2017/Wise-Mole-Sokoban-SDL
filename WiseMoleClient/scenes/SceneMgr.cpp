#include "SceneMgr.h"
#include <iterator>
#include <algorithm>

SceneMgr::SceneMgr()
{
    // Заполним запас сцен
    // Главное меню
    Scene* scn = new SCN_MainMenu();
    scn->set_name("main_menu");
    scenes.push_back(scn);

    // Пауза
    scn = new SCN_PauseMenu();
    scn->set_name("pause_menu");
    scenes.push_back(scn);

    // Игровое поле
    scn = new SCN_Level();
    scn->set_name("game_level");
    scenes.push_back(scn);

    // Поздравления с успешным прохождением
    scn = new SCN_Congrats();
    scn->set_name("congrats");
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
    GameReaction gr;

    // Очередной цикл отработки программы
    if (std::ssize(scenes) > scene_id)
    {
        gr = scenes[scene_id]->app_iter(as);
        return proc_game_reaction(gr);
    }
    else
    {
        SDL_Log("Error! Active scene_id [%i] more than scenes count!", scene_id);
        return SDL_APP_FAILURE;
    }
}

SDL_AppResult SceneMgr::proc_mouse_motion(AppState* as, float x, float y)
{
    if (std::ssize(scenes) > scene_id)
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
    if (std::ssize(scenes) > scene_id)
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
    int tmp_scene_id;

    if (scancode == SDL_SCANCODE_ESCAPE)
    {
        if (scenes[scene_id]->get_name() == "game_level")
        {
            // С игры переходим на меню паузы
            tmp_scene_id = find_scene("pause_menu");
            if (tmp_scene_id == -1)
            {
                // Требуемая сцена не найдена
                SDL_Log("Error! Scene \"%s\" not found!", "pause_menu");
                return SDL_APP_FAILURE;
            }

            scene_id_prev = scene_id;
            scene_id = tmp_scene_id;
        }
        else if (scenes[scene_id]->get_name() == "pause_menu")
        {
            // Возврат к предыдущей сцене
            tmp_scene_id = scene_id;
            scene_id = scene_id_prev;
            scene_id_prev = tmp_scene_id;
        }
    }

    if (std::ssize(scenes) > scene_id)
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
    int tmp_scene_id;

    if (gr.gr_type == GRType::ChgScene || gr.gr_type == GRType::ChgSceneWReset)
    {
        // Меняем сцену
        tmp_scene_id = find_scene(gr.adv_inf);
        if (tmp_scene_id == -1)
        {
            // Требуемая сцена не найдена
            SDL_Log("Error! Scene \"%s\" not found!", gr.adv_inf.c_str());
            return SDL_APP_FAILURE;
        }

        scene_id_prev = scene_id;
        scene_id = tmp_scene_id;

        if (gr.gr_type == GRType::ChgSceneWReset)
        {
            // Производим сброс
            scenes[scene_id]->reset();
        }
    }
    else if (gr.gr_type == GRType::PrevScene)
    {
        // Возврат к предыдущей сцене
        tmp_scene_id = scene_id;
        scene_id = scene_id_prev;
        scene_id_prev = tmp_scene_id;
    }
    else if (gr.gr_type == GRType::AppExit)
    {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

int SceneMgr::find_scene(std::string name)
{
    int id = 0;
    for (auto& scn : scenes)
    {
        if (scn->get_name() == name)
            return id;

        id++;
    }

    return -1; // Ничего не найдено
}
