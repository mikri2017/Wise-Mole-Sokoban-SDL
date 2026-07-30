#pragma once

#include "Scene.h"
#include "../ui/Button.h"
#include "../ui/Font.h"
#include "../ui/Caption.h"

class SCN_MainMenu : public Scene
{
private:
    SDL_FPoint menu_pos;
    float btn_w, btn_h;
    Button* btn_new_game, * btn_exit;

    Font* font;
    Caption* capt{ nullptr };
public:
    SCN_MainMenu();

    ~SCN_MainMenu();

    void reset();

    GameReaction app_iter(AppState *as);

    GameReaction proc_mouse_motion(AppState* as, float x, float y);

    GameReaction proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event);

    GameReaction proc_keyboard_keydown(AppState* as, SDL_Scancode scancode);
};
