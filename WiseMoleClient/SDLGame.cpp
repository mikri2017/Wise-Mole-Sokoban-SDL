#include "SDLGame.h"
#include <iostream>

SDLGame::SDLGame(SDL_Window* w, SDL_Renderer* r)
{
	window = w;
	renderer = r;

	fr.x = 0;
	fr.y = 0;
	fr.w = 50;
	fr.h = 200;
}

SDLGame::~SDLGame()
{

}

SDL_AppResult SDLGame::proc_event(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EventType::SDL_EVENT_KEY_DOWN)
	{
		if (event->key.scancode == SDL_SCANCODE_ESCAPE)
		{
			return SDL_APP_SUCCESS;
		}

		if (event->key.scancode == SDL_SCANCODE_RIGHT)
		{
			fr.x += 10;
		}

		if (event->key.scancode == SDL_SCANCODE_LEFT)
		{
			fr.x -= 10;
		}

		if (event->key.scancode == SDL_SCANCODE_UP)
		{
			fr.y -= 10;
		}

		if (event->key.scancode == SDL_SCANCODE_DOWN)
		{
			fr.y += 10;
		}
	}

	return SDL_APP_CONTINUE; // продолжим выполнение программы
}

SDL_AppResult SDLGame::app_iter(void* appstate)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &fr);

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE; // продолжим выполнение программы
}
