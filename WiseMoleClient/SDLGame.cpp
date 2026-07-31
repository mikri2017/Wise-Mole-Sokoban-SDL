#include "SDLGame.h"
#include "SoundMgr.h"
#include "VideoModeMgr.h"

SDLGame::~SDLGame()
{
    delete scn_mgr;
}

void SDLGame::init(AppState* as)
{
    // Подбираем, среди возможных, подходящий
    // полноэкранный режим
    vm_mgr.define_video_mode(as->win_w, as->win_h);
    vm_mgr.set_video_mode(as->win);

    // Запустим в работу менеджер сцен
    scn_mgr = new SceneMgr();
}

SDL_AppResult SDLGame::proc_event(AppState* as, SDL_Event* event)
{
    if (event->type == SDL_EventType::SDL_EVENT_KEY_DOWN)
    {
        if (event->key.scancode == SDL_SCANCODE_F)
        {
            if (fullscren == true)
                fullscren = false;
            else
                fullscren = true;

            SDL_SetWindowFullscreen(as->win, fullscren);
        }
        else
        {
            return scn_mgr->proc_keyboard_keydown(as, event->key.scancode);
        }
    }
    else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_MOTION)
    {
        // Движение мышкой
        return scn_mgr->proc_mouse_motion(as, event->motion.x, event->motion.y);
    }
    else if (event->type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        // Клик мышкой
        return scn_mgr->proc_mouse_button_event(as, event->button);
    }

    return SDL_APP_CONTINUE; // Продолжим выполнение программы
}

SDL_AppResult SDLGame::app_iter(AppState* as)
{
    return scn_mgr->app_iter(as);
}
