#include "SCN_MainMenu.h"
#include <iostream>

SCN_MainMenu::SCN_MainMenu()
{
    font = new Font("assets/fonts/XoloniumBold.ttf", 24);

    capt = new Caption(font);
    capt->set_font_color(255, 0, 0);
    capt->set_caption("Wise Mole Sokoban");
    capt->set_position(100.0f, 100.0f);

    btn_new_game = new Button();
    btn_new_game->set_font(font);
    btn_new_game->set_font_color(255, 0, 0);
    btn_new_game->set_caption("Новая игра");

    btn_exit = new Button();
    btn_exit->set_font(font);
    btn_exit->set_font_color(255, 0, 0);
    btn_exit->set_caption("Выход");

    reset();
}

SCN_MainMenu::~SCN_MainMenu()
{
    if (capt)
        delete capt;

    if (btn_new_game)
        delete btn_new_game;

    if (btn_exit)
        delete btn_exit;

    if (font)
        delete font;
}

void SCN_MainMenu::reset()
{
    menu_pos.x = 455;
    menu_pos.y = 384;
    btn_w = 400;
    btn_h = 70;

    btn_new_game->set_position(menu_pos.x, menu_pos.y);
    btn_new_game->set_size(btn_w, btn_h);

    btn_exit->set_position(menu_pos.x, menu_pos.y + btn_h + 30);
    btn_exit->set_size(btn_w, btn_h);
}

GameReaction SCN_MainMenu::app_iter(AppState *as)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    SDL_SetRenderDrawColor(as->r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->r);
    SDL_SetRenderDrawColor(as->r, 255, 0, 0, SDL_ALPHA_OPAQUE);

    capt->render(as->r);

    btn_new_game->render(as->r);
    btn_exit->render(as->r);

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
            if(btn_exit->check_hover(m_btn_event.x, m_btn_event.y))
            {
                // Выходим из игры
                gr.gr_type = GRType::AppExit;
                return gr;
            }

            if(btn_new_game->check_hover(m_btn_event.x, m_btn_event.y))
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
