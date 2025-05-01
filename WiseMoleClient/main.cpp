#define SDL_MAIN_USE_CALLBACKS 1  // ������������ �������� ������, ������ main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "SDLGame.h"

// ����� ������������ ���� renderer ��� ��������� � ���� ���� ������� �����
static SDL_Window* window {nullptr};
static SDL_Renderer* renderer {nullptr};

// ������� ��� ������ � ����� ���
static SDLGame* game {nullptr};

// ��� ������� ������������ ��� �������, ���� ���
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

    // ������� ������ ����
    game = new SDLGame(window, renderer);

    return SDL_APP_CONTINUE; // ��������� ���������� ���������
}

// ��� ������� ������������ ��� ����� ������� (���� ����, ������� �������, � �.�...
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // ���������� ���������, ��������� �� �� ������
    }

    return game->proc_event(appstate, event);
}

// ��� ������� ����������� ������ ���� - ������ ���������
SDL_AppResult SDL_AppIterate(void* appstate)
{
    return game->app_iter(appstate);
}

// ��� ������� ����������� ��� ���������� ���������
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    // ������� ������ ����
    delete game;

    // SDL ��������� ����, ������ ��� ���
}
