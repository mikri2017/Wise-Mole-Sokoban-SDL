#include "Box.h"

Box::Box()
{
	// Назначаем начальные координаты и размеры
	set_position(0, 0);
	fr.w = get_width();
	fr.h = get_height();

	// И капcулы столкновений
	col_c.set_area(0, 0, get_width(), get_width());
}

void Box::render(SDL_Renderer * renderer)
{
	if (in_place)
	{
		// Ящик на нужном месте
		SDL_SetRenderDrawColor(renderer, 0, 150, 0, SDL_ALPHA_OPAQUE);
	}
	else SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderFillRect(renderer, &fr);
}

void Box::set_position(float x, float y)
{
	GameObject::set_position(x, y);
	SDL_FPoint p = get_position();
	fr.x = p.x;
	fr.y = p.y;

	col_c.set_area(p.x, p.y, get_width(), get_width());
}

void Box::set_size(float w, float h)
{
	GameObject::set_size(w, h);
	fr.w = get_width();
	fr.h = get_height();

	col_c.set_area(fr.x, fr.y, get_width(), get_width());
}

void Box::move(float diff_x, float diff_y)
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

void Box::set_status(bool put_in_place)
{
	in_place = put_in_place;
}
