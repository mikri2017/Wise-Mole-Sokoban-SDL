#include "SCN_PauseMenu.h"

SCN_PauseMenu::SCN_PauseMenu()
{
    reset();
}

SCN_PauseMenu::~SCN_PauseMenu()
{
    if (btn_continue)
        delete btn_continue;

    if (btn_to_main)
        delete btn_to_main;
}

void SCN_PauseMenu::reset()
{
    menu_pos.x = 455;
    menu_pos.y = 384;
    btn_w = 400;
    btn_h = 70;
}

GameReaction SCN_PauseMenu::app_iter(AppState* as)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    if (!btn_continue)
    {
        btn_continue = new Button();
        btn_continue->init(as->r);
        btn_continue->set_caption("Продолжить");
        btn_continue->set_position(menu_pos.x, menu_pos.y);
        btn_continue->set_size(btn_w, btn_h);
    }

    if (!btn_to_main)
    {
        btn_to_main = new Button();
        btn_to_main->init(as->r);
        btn_to_main->set_caption("В главное меню");
        btn_to_main->set_position(menu_pos.x, menu_pos.y + btn_h + 30);
        btn_to_main->set_size(btn_w, btn_h);
    }

    SDL_SetRenderDrawColor(as->r, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(as->r);
    SDL_SetRenderDrawColor(as->r, 255, 0, 0, SDL_ALPHA_OPAQUE);

    btn_continue->render(as->r);
    btn_to_main->render(as->r);

    SDL_RenderPresent(as->r);

    return gr;
}

GameReaction SCN_PauseMenu::proc_mouse_motion(AppState* as, float x, float y)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    return gr;
}

GameReaction SCN_PauseMenu::proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    // Клик левой кнопкой мышки
    if (m_btn_event.button == SDL_BUTTON_LEFT)
    {
        // Один клик
        if (m_btn_event.clicks == 1)
        {
            if (btn_continue->check_hover(m_btn_event.x, m_btn_event.y))
            {
                gr.gr_type = GRType::PrevScene;
                gr.adv_inf = "";
                return gr;
            }

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

GameReaction SCN_PauseMenu::proc_keyboard_keydown(AppState* as, SDL_Scancode scancode)
{
    GameReaction gr;
    gr.gr_type = GRType::Ignore;

    return gr;
}
