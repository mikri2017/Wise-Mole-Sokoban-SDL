#pragma once

#include "Scene.h"
#include "../ui/Font.h"
#include "../ui/Caption.h"
#include "../ui/Button.h"

class SCN_Congrats : public Scene
{
private:
    SDL_FPoint menu_pos;
    float btn_w, btn_h;
    Button* btn_to_main;
    Font* font;
    Caption* cap_congrats{ nullptr };
public:
    SCN_Congrats();

    ~SCN_Congrats();

    void reset();

    GameReaction app_iter(AppState* as);

    GameReaction proc_mouse_motion(AppState* as, float x, float y);

    GameReaction proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event);

    GameReaction proc_keyboard_keydown(AppState* as, SDL_Scancode scancode);
};
