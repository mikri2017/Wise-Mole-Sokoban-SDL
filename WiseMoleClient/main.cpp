#define SDL_MAIN_USE_CALLBACKS 1  // Использовать обратные вызовы, вместо main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "SDLGame.h"

// Будем использовать этот renderer для рисования в этом окне каждого кадра
static SDL_Window* window {nullptr};
static SDL_Renderer* renderer {nullptr};

// Обертка для работы в стиле ООП
static SDLGame* game {nullptr};

// Эта функция отрабатывает при запуске, один раз
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    SDL_SetAppMetadata("WiseMole Sokoban", "0.1", "com.mikri.GAMES");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("WiseMole Sokoban", 1024, 768, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Создаем объект игры
    game = new SDLGame(window, renderer);

    return SDL_APP_CONTINUE; // продолжим выполнение программы
}

// Эта функция отрабатывает при новом событии (ввод мыши, нажатие клавиши, и т.д...
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // завершение программы, сообщение ОС об успехе
    }

    return game->proc_event(appstate, event);
}

// Эта функция запускается каждый кадр - сердце программы
SDL_AppResult SDL_AppIterate(void* appstate)
{
    return game->app_iter(appstate);
}

// Эта функция запускается при завершении программы
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    // Убираем объект игры
    delete game;

    // SDL освободит окно, рендер для нас
}
