#include "SCN_MainMenu.h"
#include <iostream>

SCN_MainMenu::SCN_MainMenu()
{
    reset();
}

SCN_MainMenu::~SCN_MainMenu()
{
}

void SCN_MainMenu::reset()
{
    menuPosition.x = 455;
    menuPosition.y = 384;
    btn_w = 400;
    btn_h = 70;

    // Задаем параметры кнопок
    btn_new_game.set_caption("NEW GAME");
    btn_new_game.set_position(menuPosition.x, menuPosition.y);
    btn_new_game.set_size(btn_w, btn_h);

    btn_exit.set_caption("EXIT");
    btn_exit.set_position(menuPosition.x, menuPosition.y + btn_h + 30);
    btn_exit.set_size(btn_w, btn_h);
}

GameReaction SCN_MainMenu::app_iter(AppState *as)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    SDL_SetRenderDrawColor(as->r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->r);
    SDL_SetRenderDrawColor(as->r, 255, 0, 0, SDL_ALPHA_OPAQUE);

    btn_new_game.render(as->r);
    btn_exit.render(as->r);

    SDL_RenderPresent(as->r);

    return gr;
}

GameReaction SCN_MainMenu::proc_mouse_motion(AppState* as, float x, float y)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    return gr;
}

GameReaction SCN_MainMenu::proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    // Клик левой кнопкой мышки
    if(m_btn_event.button == SDL_BUTTON_LEFT)
    {
        // Один клик
        if(m_btn_event.clicks == 1)
        {
            if(btn_exit.check_hover(m_btn_event.x, m_btn_event.y))
            {
                // Выходим из игры
                gr.gr_type = GRType::AppExit;
                return gr;
            }

            if(btn_new_game.check_hover(m_btn_event.x, m_btn_event.y))
            {
                gr.gr_type = GRType::ChgSceneWReset;
                gr.adv_inf = "game_level";
                return gr;
            }
        }
    }

    return gr;
}

GameReaction SCN_MainMenu::proc_keyboard_keydown(AppState* as, SDL_Scancode scancode)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    return gr;
}
