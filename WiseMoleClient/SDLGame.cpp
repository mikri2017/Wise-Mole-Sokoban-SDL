#include "SDLGame.h"
#include "VideoModeMgr.h"
#include <iostream>

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

	float block_size = 50;

	// Разместим персонажа
	hero.set_position(area.x, area.y);
	hero.set_size(block_size, block_size);
	hero.set_max_hp(100);

	// Накидаем стены
	SDL_FPoint pw[10]{
		{area.x + block_size * 2, area.y + block_size},
		{area.x + block_size * 3, area.y + block_size},
		{area.x + block_size * 5, area.y + block_size},
		{area.x + block_size * 9, area.y + block_size},
		{area.x + block_size * 3, area.y + block_size * 3},
		{area.x + block_size * 5, area.y + block_size * 2},
		{area.x + block_size * 7, area.y + block_size * 5},
		{area.x + block_size * 8, area.y + block_size * 5},
		{area.x + block_size * 9, area.y + block_size * 9},
		{area.x + block_size * 12, area.y + block_size * 7}
	};

	for (auto i = 0; i < 10; i++)
	{
		WallBlock wb;
		wb.set_position(pw[i].x, pw[i].y);
		wb.set_size(block_size, block_size);
		w_blocks.push_back(wb);
	}

	// Добавим места под ящики
	SDL_FPoint pbp[3]{
		{area.x + block_size * 2, area.y + block_size * 5},
		{area.x + block_size * 2, area.y + block_size * 6},
		{area.x + block_size * 4, area.y + block_size * 5}
	};

	for (auto i = 0; i < 3; i++)
	{
		BoxPlace bp;
		bp.set_position(pbp[i].x, pbp[i].y);
		bp.set_size(block_size, block_size);
		b_places.push_back(bp);
	}

	// Добавим ящики
	SDL_FPoint pb[3]{
		{area.x + block_size * 3, area.y + block_size * 5},
		{area.x + block_size * 2, area.y + block_size * 7},
		{area.x + block_size * 7, area.y + block_size * 7}
	};

	for (auto i = 0; i < 3; i++)
	{
		Box b;
		b.set_position(pb[i].x, pb[i].y);
		b.set_size(block_size, block_size);
		boxes.push_back(b);
	}
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
			if (check_collisions_immv(hero) ||
				check_collisions_boxes(hero, step, 0))
				hero.move(-step, 0); // Столкновение, откатываем
		}

		if (event->key.scancode == SDL_SCANCODE_LEFT)
		{
			hero.move(-step, 0);
			if (check_collisions_immv(hero) ||
				check_collisions_boxes(hero, -step, 0))
				hero.move(step, 0); // Вышли за пределы, откатываем
		}

		if (event->key.scancode == SDL_SCANCODE_UP)
		{
			hero.move(0, -step);
			if (check_collisions_immv(hero) ||
				check_collisions_boxes(hero, 0, -step))
				hero.move(0, step); // Вышли за пределы, откатываем
		}

		if (event->key.scancode == SDL_SCANCODE_DOWN)
		{
			hero.move(0, step);
			if (check_collisions_immv(hero) ||
				check_collisions_boxes(hero, 0, step))
				hero.move(0, -step); // Вышли за пределы, откатываем
		}

		if (check_for_win())
			std::cout << "POBEDA!!!" << std::endl;
	}

	return SDL_APP_CONTINUE; // Продолжим выполнение программы
}

SDL_AppResult SDLGame::app_iter(void* appstate)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	for (auto& w_block : w_blocks)
	{
		w_block.render(renderer);
	}

	for (auto& b_place : b_places)
	{
		b_place.render(renderer);
	}

	for (auto& box : boxes)
	{
		box.render(renderer);
	}

	// Персонаж рисуется последним,
	// чтобы не закрасило
	hero.render(renderer);

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE; // Продолжим выполнение программы
}

bool SDLGame::check_collisions_immv(GameObject game_o)
{
	// Проверка, что не вышли за пределы поля
	if (!game_o.check_inside(&loc_area))
		return true; // Вышли за пределы, откатываем

	// Провека на столкновения с несдвигаемыми объектами
	for (auto& w_block : w_blocks)
	{
		if (game_o.check_collision(w_block))
			return true;
	}

	return false;
}

bool SDLGame::check_collisions_boxes(GameObject game_o, float diff_x, float diff_y)
{
	// Провека на столкновения с ящиками
	for (auto& box : boxes)
	{
		if (game_o.check_collision(box))
		{
			box.move(diff_x, diff_y);
			if (check_collisions_immv(box))
			{
				box.move(-diff_x, -diff_y);
				return true;
			}

			// Сдвигаемый ящик не должен двигаться,
			// если мешает другой такой же или стена
			for (auto& box_c : boxes)
			{
				if (&box_c != &box)
				{
					if (box.check_collision(box_c))
					{
						box.move(-diff_x, -diff_y);
						return true;
					}
				}
			}

			// Ящик сдвинут, проверяем его нахождение
			// в нужном месте
			for (auto& b_place : b_places)
			{
				if (box.check_inside(&b_place))
				{
					box.set_status(true);
					break; // Ящик может быть только в одном месте
				}
				else box.set_status(false);
			}
		}
	}

	return false;
}

bool SDLGame::check_for_win()
{
	// Проверим, что все ящики на своих местах
	for (auto& box : boxes)
	{
		bool in_place = false;
		for (auto& b_place : b_places)
		{
			if (box.check_inside(&b_place))
			{
				in_place = true;
				break;
			}
		}

		if (!in_place)
			return false; // Ящик не на месте
	}

	// Все ящики на своих местах
	return true;
}
