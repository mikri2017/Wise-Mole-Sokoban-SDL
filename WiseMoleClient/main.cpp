#define SDL_MAIN_USE_CALLBACKS 1  // Использовать обратные вызовы, вместо main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include "SDLGame.h"
#include "AppState.h"

// Обертка для работы в стиле ООП
static SDLGame* game {nullptr};

// Эта функция отрабатывает при запуске, один раз
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    std::string app_title{ "WiseMole Sokoban" };

    SDL_SetAppMetadata(app_title.c_str(), "0.1", "com.mikri.GAMES");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Инициализация шрифтов и текста
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState* as = new AppState();
    if (!SDL_CreateWindowAndRenderer(app_title.c_str(), as->win_w, as->win_h, 0, &(as->win), &(as->r))) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Инициализируем менеджер звуков
    // SDL3 Mixer работает только через указатели
    as->snd_mgr = new SoundMgr();

    *appstate = as;

    // Создаем объект игры
    game = new SDLGame();
    game->init(as);

    return SDL_APP_CONTINUE; // Продолжим выполнение программы
}

// Эта функция отрабатывает при новом событии (ввод мыши, нажатие клавиши, и т.д...
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // Завершение программы, сообщение ОС об успехе
    }

    return game->proc_event((AppState*)appstate, event);
}

// Эта функция запускается каждый кадр - сердце программы
SDL_AppResult SDL_AppIterate(void* appstate)
{
    return game->app_iter((AppState*)appstate);
}

// Эта функция запускается при завершении программы
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    AppState* as = (AppState*)appstate;
    if (as) {
        SDL_DestroyRenderer(as->r);
        SDL_DestroyWindow(as->win);
        delete as->snd_mgr;
        delete as;
    }

    // Убираем объект игры
    delete game;

    // Убираем работу со шрифтами и текстом
    TTF_Quit();

    // SDL освободит окно, рендер для нас
}
