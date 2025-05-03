#include <iostream>
#include "SDLGame.h"
#include "VideoModeMgr.h"

SDLGame::SDLGame(SDL_Window* w, SDL_Renderer* r)
{
	window = w;
	renderer = r;

	// Получим доступные режимы работы монитора
	vm_mgr.reload_modes();
	vvm_str = vm_mgr.get_available_modes();
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

		if (event->key.scancode == SDL_SCANCODE_I)
		{
			// Предыдущий режим работы
			active_vm--;
			if (active_vm < 1)
				active_vm = 1;

			std::cout << "Selected mode (" << vvm_str.size() << "): " << vvm_str[active_vm].mode_name << std::endl;
		}

		if (event->key.scancode == SDL_SCANCODE_O)
		{
			// Следующий режим работы
			active_vm++;
			if (active_vm >= vvm_str.size())
				active_vm = vvm_str.size() - 1;

			std::cout << "Selected mode (" << vvm_str.size() << "): " << vvm_str[active_vm].mode_name << std::endl;
		}

		if (event->key.scancode == SDL_SCANCODE_RETURN)
		{
			// Перейти в этот режим
			if (!vm_mgr.set_video_mode(window, active_vm))
				std::cout << "Unavailable mode!" << std::endl;
			else
				std::cout << "Mode is seted!" << std::endl;
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
