#include "MainHero.h"
#include <iostream>

MainHero::MainHero()
{
	// Назначаем начальные координаты
	// и размеры героя
	set_position(0, 0);	
	fr.w = w;
	fr.h = h;

	// И капсулы столкновений
	col_c.set_area(0, 0, w, h);
}

void MainHero::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &fr);
}

void MainHero::set_position(float x, float y)
{
	GameObject::set_position(x, y);
	SDL_FPoint p = get_position();
	fr.x = p.x;
	fr.y = p.y;

	col_c.set_area(p.x, p.y, w, h);
}

void MainHero::move(float diff_x, float diff_y)
{
	// Перемещаем объект
	GameObject::move(diff_x, diff_y);

	// Обновляем позицию для рисовки
	SDL_FPoint p = get_position();
	fr.x = p.x;
	fr.y = p.y;

	// И расположение капсулы столкновений
	col_c.set_area(fr.x, fr.y, fr.w, fr.h);
}
