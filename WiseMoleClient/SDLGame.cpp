#include <iostream>
#include "SDLGame.h"
#include "VideoModeMgr.h"

SDLGame::SDLGame(SDL_Window* win, SDL_Renderer* r)
{
	window = win;
	renderer = r;

	// Получим размеры текущего окна
	SDL_GetWindowSize(window, &win_w, &win_h);

	// Подбираем, среди возможных, подходящий
	// полноэкранный режим
	vm_mgr.define_video_mode(win_w, win_h);
	vm_mgr.set_video_mode(window);
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

		if (event->key.scancode == SDL_SCANCODE_F)
		{
			if (fullscren == true)
				fullscren = false;
			else
				fullscren = true;

			SDL_SetWindowFullscreen(window, fullscren);
		}

		if (event->key.scancode == SDL_SCANCODE_RIGHT)
		{
			fr.x += step;
			if (fr.x + fr.w > win_w)
			{
				fr.x = win_w - fr.w;
			}
		}

		if (event->key.scancode == SDL_SCANCODE_LEFT)
		{
			fr.x -= step;
			if (fr.x < 0)
			{
				fr.x = 0;
			}
		}

		if (event->key.scancode == SDL_SCANCODE_UP)
		{
			fr.y -= step;
			if (fr.y < 0)
			{
				fr.y = 0;
			}
		}

		if (event->key.scancode == SDL_SCANCODE_DOWN)
		{
			fr.y += step;
			if (fr.y + fr.h > win_h)
			{
				fr.y = win_h - fr.h;
			}
		}
	}

	return SDL_APP_CONTINUE; // Продолжим выполнение программы
}

SDL_AppResult SDLGame::app_iter(void* appstate)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &fr);

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE; // Продолжим выполнение программы
}
