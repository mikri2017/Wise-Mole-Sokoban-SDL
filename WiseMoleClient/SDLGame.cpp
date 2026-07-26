#include <iostream>
#include "SDLGame.h"
#include "VideoModeMgr.h"

SDLGame::SDLGame(SDL_Window* win, SDL_Renderer* r)
{
	// Сохраним указатели на окно и рендер
	// для внутреннего использования
	window = win;
	renderer = r;

	// Получим размеры текущего окна
	SDL_Rect w_area;
	SDL_GetWindowSafeArea(window, &w_area);

	// Подбираем, среди возможных, подходящий
	// полноэкранный режим
	vm_mgr.define_video_mode(w_area.w, w_area.h);
	vm_mgr.set_video_mode(window);

	// Назначим зону уровня для перемещения
	float pos_x{ 33 }, pos_y{ 34 };
	loc_area.set_area(pos_x, pos_y, 1300, 500);

	SDL_FRect area = loc_area.get_area();

	// Разместим персонажа
	hero.set_position(area.x, area.y);
	hero.set_max_hp(100);
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
			hero.move(step, 0);
			if (!hero.check_inside(&loc_area))
				hero.move(-step, 0); // Вышли за пределы, откатываем
		}

		if (event->key.scancode == SDL_SCANCODE_LEFT)
		{
			hero.move(-step, 0);
			if (!hero.check_inside(&loc_area))
				hero.move(step, 0); // Вышли за пределы, откатываем
		}

		if (event->key.scancode == SDL_SCANCODE_UP)
		{
			hero.move(0, -step);
			if (!hero.check_inside(&loc_area))
				hero.move(0, step); // Вышли за пределы, откатываем
		}

		if (event->key.scancode == SDL_SCANCODE_DOWN)
		{
			hero.move(0, step);
			if (!hero.check_inside(&loc_area))
				hero.move(0, -step); // Вышли за пределы, откатываем
		}
	}

	return SDL_APP_CONTINUE; // Продолжим выполнение программы
}

SDL_AppResult SDLGame::app_iter(void* appstate)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	hero.render(renderer);

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE; // Продолжим выполнение программы
}
