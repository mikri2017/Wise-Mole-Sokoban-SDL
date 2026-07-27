#include "SCN_Level.h"

SCN_Level::SCN_Level()
{
	// Назначим зону уровня для перемещения
	float area_x{ 33 },
		area_y{ 34 },
		area_w{ 1300 },
		area_h{ 500 };

	loc_area.set_area(area_x, area_y, area_w, area_h);

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

SDL_AppResult SCN_Level::app_iter(AppState* as)
{
	SDL_SetRenderDrawColor(as->r, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(as->r);

	for (auto& w_block : w_blocks)
	{
		w_block.render(as->r);
	}

	for (auto& b_place : b_places)
	{
		b_place.render(as->r);
	}

	for (auto& box : boxes)
	{
		box.render(as->r);
	}

	// Персонаж рисуется последним,
	// чтобы не закрасило
	hero.render(as->r);

	SDL_RenderPresent(as->r);

	return SDL_APP_CONTINUE; // Продолжим выполнение программы
}

GameReaction SCN_Level::proc_mouse_motion(AppState* as, float x, float y)
{
    return GameReaction();
}

GameReaction SCN_Level::proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event)
{
    return GameReaction();
}

GameReaction SCN_Level::proc_keyboard_keydown(AppState* as, SDL_Scancode scancode)
{
	GameReaction gr;
	gr.gr_type = GRType::GR_IGNORE;

	if (scancode == SDL_SCANCODE_RIGHT)
	{
		hero.move(step, 0);
		if (check_collisions_immv(hero) ||
			check_collisions_boxes(as->snd_mgr, hero, step, 0))
			hero.move(-step, 0); // Столкновение, откатываем
	}

	if (scancode == SDL_SCANCODE_LEFT)
	{
		hero.move(-step, 0);
		if (check_collisions_immv(hero) ||
			check_collisions_boxes(as->snd_mgr, hero, -step, 0))
			hero.move(step, 0); // Вышли за пределы, откатываем
	}

	if (scancode == SDL_SCANCODE_UP)
	{
		hero.move(0, -step);
		if (check_collisions_immv(hero) ||
			check_collisions_boxes(as->snd_mgr, hero, 0, -step))
			hero.move(0, step); // Вышли за пределы, откатываем
	}

	if (scancode == SDL_SCANCODE_DOWN)
	{
		hero.move(0, step);
		if (check_collisions_immv(hero) ||
			check_collisions_boxes(as->snd_mgr, hero, 0, step))
			hero.move(0, -step); // Вышли за пределы, откатываем
	}

	if (check_for_win())
	{
		// Победили, отправляем на сцену поздравления
		gr.gr_type = GRType::GR_CHG_SCENE;
		gr.adv_inf = "congrats";
	}

	return gr;
}

bool SCN_Level::check_collisions_immv(GameObject game_o)
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

bool SCN_Level::check_collisions_boxes(SoundMgr* snd_mgr, GameObject game_o, float diff_x, float diff_y)
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

			// Ящик сдвинули, проигрываем звук
			snd_mgr->play_sound(SndType::t_move_box);

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

bool SCN_Level::check_for_win()
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
