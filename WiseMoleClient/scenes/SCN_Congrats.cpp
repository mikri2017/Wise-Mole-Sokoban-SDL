#include "SCN_Congrats.h"

SCN_Congrats::SCN_Congrats()
{
    font = new Font("assets/fonts/XoloniumBold.ttf", 24);

    cap_congrats = new Caption(font);
    cap_congrats->set_font_color(255, 0, 0);
    cap_congrats->set_caption("Поздравляем! Вы прошли уровень!");
    cap_congrats->set_position(100.0f, 100.0f);

    btn_to_main = new Button();
    btn_to_main->set_font(font);
    btn_to_main->set_font_color(255, 0, 0);
    btn_to_main->set_caption("В главное меню");

    reset();    
}

SCN_Congrats::~SCN_Congrats()
{
    if (btn_to_main)
        delete btn_to_main;

    // if (font)
    //     delete font;
}

void SCN_Congrats::reset()
{
    menu_pos.x = 455;
    menu_pos.y = 512;
    btn_w = 400;
    btn_h = 70;

    btn_to_main->set_position(menu_pos.x, menu_pos.y);
    btn_to_main->set_size(btn_w, btn_h);
}

GameReaction SCN_Congrats::app_iter(AppState* as)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    SDL_SetRenderDrawColor(as->r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->r);
    SDL_SetRenderDrawColor(as->r, 255, 0, 0, SDL_ALPHA_OPAQUE);

    cap_congrats->render(as->r);

    btn_to_main->render(as->r);

    SDL_RenderPresent(as->r);

    SDL_Delay(50);

    return gr;
}

GameReaction SCN_Congrats::proc_mouse_motion(AppState* as, float x, float y)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    return gr;
}

GameReaction SCN_Congrats::proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    // Клик левой кнопкой мышки
    if (m_btn_event.button == SDL_BUTTON_LEFT)
    {
        // Один клик
        if (m_btn_event.clicks == 1)
        {
            if (btn_to_main->check_hover(m_btn_event.x, m_btn_event.y))
            {
                gr.gr_type = GRType::ChgSceneWReset;
                gr.adv_inf = "main_menu";
                return gr;
            }
        }
    }

    return gr;
}

GameReaction SCN_Congrats::proc_keyboard_keydown(AppState* as, SDL_Scancode scancode)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    return gr;
}
