#pragma once

#include <string>
#include <SDL3/SDL.h>
#include "../AppState.h"
#include "GameReaction.h"

class Scene
{
private:
    std::string name;
public:
    std::string get_name();

    bool set_name(std::string s_name);

    virtual void reset() = 0;

    virtual GameReaction app_iter(AppState* as) = 0;

    virtual GameReaction proc_mouse_motion(AppState* as, float x, float y) = 0;

    virtual GameReaction proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event) = 0;

    virtual GameReaction proc_keyboard_keydown(AppState* as, SDL_Scancode scancode) = 0;
};
