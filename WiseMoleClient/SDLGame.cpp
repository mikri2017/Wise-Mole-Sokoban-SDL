#include "SDLGame.h"
#include <iostream>

SDLGame::SDLGame(SDL_Window* w, SDL_Renderer* r)
{
	window = w;
	renderer = r;

	// Получить и показать доступные режимы монитора
	/*SDL_DisplayMode** dm;

	dm = SDL_GetFullscreenDisplayModes(SDL_GetPrimaryDisplay(), nullptr);

	SDL_DisplayMode** ptr;

	for (ptr = dm; *ptr != nullptr; ptr++) {
		std::cout << "DM: " << (*ptr)->format << " - "
			<< (*ptr)->w << " - " << (*ptr)->h << " - "
			<< (*ptr)->pixel_density << " - " << (*ptr)->refresh_rate << std::endl;
	}*/

	// Как пример, установил конкретный режим
	SDL_DisplayMode dm_test;
	dm_test.displayID = SDL_GetPrimaryDisplay();
	dm_test.format = SDL_PIXELFORMAT_XRGB8888;
	dm_test.w = 1024;
	dm_test.h = 768;
	dm_test.pixel_density = 1;
	dm_test.refresh_rate = 60;

	// Устанавливаем параметры полноэкранного режима
	SDL_SetWindowFullscreenMode(window, &dm_test);

	// Устанавливаем заданный, по умолчанию, режим (полный экран/окно)
	SDL_SetWindowFullscreen(window, fullscren);
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

		if (event->key.scancode == SDL_SCANCODE_F)
		{
			if (fullscren == true)
				fullscren = false;
			else
				fullscren = true;

			SDL_SetWindowFullscreen(window, fullscren);
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
