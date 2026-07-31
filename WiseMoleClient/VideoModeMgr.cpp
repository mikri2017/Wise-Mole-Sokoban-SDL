#include "VideoModeMgr.h"
#include <iostream>

VideoModeMgr::VideoModeMgr()
{
    // Получим герцовку текущего режима монитора
    const SDL_DisplayMode* dm_cur_sys;
    dm_cur_sys = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
    refresh_rate = dm_cur_sys->refresh_rate;
}

bool VideoModeMgr::define_video_mode(int w, int h)
{
    // Получаем доступные режимы монитора
    SDL_DisplayMode** dms;

    dms = SDL_GetFullscreenDisplayModes(SDL_GetPrimaryDisplay(), nullptr);
    if (dms == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    // Обходим режимы, подбираем нужный
    SDL_DisplayMode** ptr;
    for (ptr = dms; *ptr != nullptr; ptr++)
    {
        if ((*ptr)->refresh_rate == refresh_rate)
        {
            // Частота подошла, выбираем разрешение
            if ((*ptr)->w == w && (*ptr)->h == h)
            {
                dm = (*ptr);
            }
        }
    }

    SDL_free(dms);

    return true;
}

bool VideoModeMgr::set_video_mode(SDL_Window* w)
{
    if (dm)
    {
        // Устанавливаем выбранный режим работы экрана
        SDL_SetWindowFullscreenMode(w, dm);
    }
    else
        return false;

    return true;
}
