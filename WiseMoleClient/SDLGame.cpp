#include "SDLGame.h"
#include <iostream>

SDLGame::SDLGame(SDL_Window* w, SDL_Renderer* r)
{
	window = w;
	renderer = r;
}

SDLGame::~SDLGame()
{

}

SDL_AppResult SDLGame::proc_event(void* appstate, SDL_Event* event)
{
	return SDL_APP_CONTINUE; // продолжим выполнение программы
}

SDL_AppResult SDLGame::app_iter(void* appstate)
{
	return SDL_APP_CONTINUE; // продолжим выполнение программы
}
