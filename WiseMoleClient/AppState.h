#pragma once

#include <SDL3/SDL.h>
#include "SoundMgr.h"

class AppState
{
public:
    SDL_Window* win{ nullptr };
    SDL_Renderer* r{ nullptr };
    const int win_w{ 1366 }; // Ширина окна
    const int win_h{ 768 }; // Высота окна

    SoundMgr* snd_mgr{ nullptr };
};
